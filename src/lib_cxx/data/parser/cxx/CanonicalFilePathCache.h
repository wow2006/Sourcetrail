#ifndef CANONICAL_FILE_PATH_CACHE_H
#define CANONICAL_FILE_PATH_CACHE_H

#include <map>
#include <string>
#include <unordered_map>

#include <clang/AST/Decl.h>
#include <clang/Basic/SourceManager.h>

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "FileRegister.h"
#include "types.h"

class CanonicalFilePathCache
{
public:
	CanonicalFilePathCache(std::shared_ptr<utility::file::FileRegister> fileRegister);

	std::shared_ptr<utility::file::FileRegister> getFileRegister() const;

	utility::file::FilePath getCanonicalFilePath(const clang::FileID& fileId, const clang::SourceManager& sourceManager);
	utility::file::FilePath getCanonicalFilePath(const clang::FileEntry* entry);
	utility::file::FilePath getCanonicalFilePath(const std::wstring& path);
	utility::file::FilePath getCanonicalFilePath(const Id symbolId);

	void addFileSymbolId(const clang::FileID& fileId, const utility::file::FilePath& path, Id symbolId);
	Id getFileSymbolId(const clang::FileID& fileId);
	Id getFileSymbolId(const clang::FileEntry* entry);
	Id getFileSymbolId(const std::wstring& path);

	utility::file::FilePath getDeclarationFilePath(const clang::Decl* declaration);
	std::wstring getDeclarationFileName(const clang::Decl* declaration);

	bool isProjectFile(const clang::FileID& fileId, const clang::SourceManager& sourceManager);

private:
	std::shared_ptr<utility::file::FileRegister> m_fileRegister;

	std::map<clang::FileID, utility::file::FilePath> m_fileIdMap;
	std::unordered_map<std::wstring, utility::file::FilePath> m_fileStringMap;

	std::map<clang::FileID, Id> m_fileIdSymbolIdMap;
	std::map<Id, clang::FileID> m_symbolIdFileIdMap;
	std::unordered_map<std::wstring, Id> m_fileStringSymbolIdMap;

	std::map<clang::FileID, bool> m_isProjectFileMap;
};

#endif	  // CANONICAL_FILE_PATH_CACHE_H
