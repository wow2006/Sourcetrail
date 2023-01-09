#ifndef CXX_DIAGNOSTIC_CONSUMER
#define CXX_DIAGNOSTIC_CONSUMER

#include "FilePath.h"
#include <clang/Frontend/TextDiagnosticPrinter.h>

class CanonicalFilePathCache;
class ParserClient;

class CxxDiagnosticConsumer: public clang::TextDiagnosticPrinter
{
public:
	CxxDiagnosticConsumer(
		clang::raw_ostream& os,
		clang::DiagnosticOptions* diags,
		std::shared_ptr<ParserClient> client,
		std::shared_ptr<CanonicalFilePathCache> canonicalFilePathCache,
		const utility::file::FilePath& sourceFilePath,
		bool useLogging = true);

	void BeginSourceFile(
		const clang::LangOptions& langOptions, const clang::Preprocessor* preProcessor) override;
	void EndSourceFile() override;

	void HandleDiagnostic(clang::DiagnosticsEngine::Level level, const clang::Diagnostic& info) override;

private:
	std::shared_ptr<ParserClient> m_client;
	std::shared_ptr<CanonicalFilePathCache> m_canonicalFilePathCache;

	const utility::file::FilePath m_sourceFilePath;
	bool m_useLogging;
};

#endif	  // CXX_DIAGNOSTIC_CONSUMER
