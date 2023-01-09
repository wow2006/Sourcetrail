#include "catch.hpp"

#include "FileSystem.h"
#include "SqliteBookmarkStorage.h"

TEST_CASE("add bookmarks")
{
	utility::file::FilePath databasePath(L"data/SQLiteTestSuite/bookmarkTest.sqlite");
	size_t bookmarkCount = 4;
	int result = -1;
	{
		utility::file::FileSystem::remove(databasePath);
		SqliteBookmarkStorage storage(databasePath);
		storage.setup();

		for (size_t i = 0; i < bookmarkCount; i++)
		{
			const Id categoryId =
				storage.addBookmarkCategory(StorageBookmarkCategoryData(L"test category")).id;
			storage.addBookmark(StorageBookmarkData(
				L"test bookmark", L"test comment", TimeStamp::now().toString(), categoryId));
		}

		result = static_cast<int>(storage.getAllBookmarks().size());
	}

	utility::file::FileSystem::remove(databasePath);

	REQUIRE(result == bookmarkCount);
}

TEST_CASE("add bookmarked node")
{
	utility::file::FilePath databasePath(L"data/SQLiteTestSuite/bookmarkTest.sqlite");
	size_t bookmarkCount = 4;
	int result = -1;
	{
		utility::file::FileSystem::remove(databasePath);
		SqliteBookmarkStorage storage(databasePath);
		storage.setup();

		const Id categoryId =
			storage.addBookmarkCategory(StorageBookmarkCategoryData(L"test category")).id;
		const Id bookmarkId =
			storage
				.addBookmark(StorageBookmarkData(
					L"test bookmark", L"test comment", TimeStamp::now().toString(), categoryId))
				.id;

		for (size_t i = 0; i < bookmarkCount; i++)
		{
			storage.addBookmarkedNode(StorageBookmarkedNodeData(bookmarkId, L"test name"));
		}

		result = static_cast<int>(storage.getAllBookmarkedNodes().size());
	}

	utility::file::FileSystem::remove(databasePath);

	REQUIRE(result == bookmarkCount);
}

TEST_CASE("remove bookmark also removes bookmarked node")
{
	utility::file::FilePath databasePath(L"data/SQLiteTestSuite/bookmarkTest.sqlite");
	int result = -1;
	{
		utility::file::FileSystem::remove(databasePath);
		SqliteBookmarkStorage storage(databasePath);
		storage.setup();

		const Id categoryId =
			storage.addBookmarkCategory(StorageBookmarkCategoryData(L"test category")).id;
		const Id bookmarkId =
			storage
				.addBookmark(StorageBookmarkData(
					L"test bookmark", L"test comment", TimeStamp::now().toString(), categoryId))
				.id;
		storage.addBookmarkedNode(StorageBookmarkedNodeData(bookmarkId, L"test name"));

		storage.removeBookmark(bookmarkId);

		result = static_cast<int>(storage.getAllBookmarkedNodes().size());
	}

	utility::file::FileSystem::remove(databasePath);

	REQUIRE(result == 0);
}

TEST_CASE("edit nodeBookmark")
{
	utility::file::FilePath databasePath(L"data/SQLiteTestSuite/bookmarkTest.sqlite");

	const std::wstring updatedName = L"updated name";
	const std::wstring updatedComment = L"updated comment";

	StorageBookmark storageBookmark;
	{
		utility::file::FileSystem::remove(databasePath);
		SqliteBookmarkStorage storage(databasePath);
		storage.setup();

		const Id categoryId =
			storage.addBookmarkCategory(StorageBookmarkCategoryData(L"test category")).id;
		const Id bookmarkId =
			storage
				.addBookmark(StorageBookmarkData(
					L"test bookmark", L"test comment", TimeStamp::now().toString(), categoryId))
				.id;
		storage.addBookmarkedNode(StorageBookmarkedNodeData(bookmarkId, L"test name"));

		storage.updateBookmark(bookmarkId, updatedName, updatedComment, categoryId);

		storageBookmark = storage.getAllBookmarks().front();
	}

	utility::file::FileSystem::remove(databasePath);

	REQUIRE(updatedName == storageBookmark.name);
	REQUIRE(updatedComment == storageBookmark.comment);
}
