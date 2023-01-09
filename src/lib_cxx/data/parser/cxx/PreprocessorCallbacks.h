#ifndef PREPROCESSOR_CALLBACKS_H
#define PREPROCESSOR_CALLBACKS_H

#include <memory>
#include <set>

#include <clang/Basic/SourceManager.h>
#include <clang/Lex/MacroInfo.h>
#include <clang/Lex/PPCallbacks.h>
#include <clang/Lex/Token.h>

#include "types.h"

class CanonicalFilePathCache;
class ParserClient;

struct ParseLocation;

class PreprocessorCallbacks: public clang::PPCallbacks
{
public:
	explicit PreprocessorCallbacks(
		clang::SourceManager& sourceManager,
		std::shared_ptr<ParserClient> client,
		std::shared_ptr<CanonicalFilePathCache> canonicalFilePathCache);

	void FileChanged(
		clang::SourceLocation location,
		FileChangeReason reason,
		clang::SrcMgr::CharacteristicKind,
		clang::FileID) override;

	void InclusionDirective(
		clang::SourceLocation hashLocation,
		const clang::Token& includeToken,
		llvm::StringRef fileName,
		bool isAngled,
		clang::CharSourceRange fileNameRange,
		const clang::FileEntry* fileEntry,
		llvm::StringRef searchPath,
		llvm::StringRef relativePath,
		const clang::Module* imported,
		clang::SrcMgr::CharacteristicKind fileType) override;

	void MacroDefined(
		const clang::Token& macroNameToken, const clang::MacroDirective* macroDirective) override;
	void MacroUndefined(
		const clang::Token& macroNameToken,
		const clang::MacroDefinition& macroDefinition,
		const clang::MacroDirective* macroUndefinition) override;

	void Defined(
		const clang::Token& macroNameToken,
		const clang::MacroDefinition& macroDefinition,
		clang::SourceRange range) override;
	void Ifdef(
		clang::SourceLocation location,
		const clang::Token& macroNameToken,
		const clang::MacroDefinition& macroDefinition) override;
	void Ifndef(
		clang::SourceLocation location,
		const clang::Token& macroNameToken,
		const clang::MacroDefinition& macroDefinition) override;

	void MacroExpands(
		const clang::Token& macroNameToken,
		const clang::MacroDefinition& macroDirective,
		clang::SourceRange range,
		const clang::MacroArgs* args) override;

private:
	void onMacroUsage(const clang::Token& macroNameToken);

	ParseLocation getParseLocation(const clang::Token& macroNameToc) const;
	ParseLocation getParseLocation(const clang::MacroInfo* macroNameToc) const;
	ParseLocation getParseLocation(const clang::SourceRange& sourceRange) const;
	bool isLocatedInProjectFile(const clang::SourceLocation loc);

	const clang::SourceManager& m_sourceManager;
	std::shared_ptr<ParserClient> m_client;
	std::shared_ptr<CanonicalFilePathCache> m_canonicalFilePathCache;

	Id m_currentFileSymbolId;
	bool m_currentPathIsProjectFile = false;

	std::set<clang::FileID> m_fileWasRecorded;
};

#endif	  // PREPROCESSOR_CALLBACKS_H
