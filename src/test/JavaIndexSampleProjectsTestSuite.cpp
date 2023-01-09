#include "catch.hpp"

#include "language_packages.h"

#if BUILD_JAVA_LANGUAGE_PACKAGE

#	include <fstream>

#	include "ApplicationSettings.h"
#	include "FileRegister.h"
#	include "IndexerCommandJava.h"
#	include "JavaEnvironmentFactory.h"
#	include "JavaParser.h"
#	include "ParserClientImpl.h"
#	include "TestStorage.h"
#	include "TextAccess.h"
#	include "TimeStamp.h"
#	include "utility.h"
#	include "utilityJava.h"
#	include "utilityPathDetection.h"
#	include "utilityString.h"

#	define REQUIRE_MESSAGE(msg, cond)                                                             \
		do                                                                                         \
		{                                                                                          \
			INFO(msg);                                                                             \
			REQUIRE(cond);                                                                         \
		} while ((void)0, 0)

namespace
{
const bool updateExpectedOutput = false;
const bool trackTime = true;
size_t duration;

void setupJavaEnvironmentFactory()
{
	if (!JavaEnvironmentFactory::getInstance())
	{
		std::string errorString;
#	ifdef _WIN32
		const std::string separator = ";";
#	else
		const std::string separator = ":";
#	endif
		std::string classPath = "";
		{
			const std::vector<std::wstring> jarNames = utility::getRequiredJarNames();
			for (size_t i = 0; i < jarNames.size(); i++)
			{
				if (i != 0)
				{
					classPath += separator;
				}
				classPath += utility::file::FilePath(L"../app/data/java/lib/").concatenate(jarNames[i]).str();
			}
		}

		JavaEnvironmentFactory::createInstance(classPath, errorString);
	}
}

std::shared_ptr<TextAccess> parseCode(
	const utility::file::FilePath& sourceFilePath,
	const utility::file::FilePath& projectDataSrcRoot,
	const std::vector<utility::file::FilePath>& classpath)
{
	std::shared_ptr<IntermediateStorage> storage = std::make_shared<IntermediateStorage>();
	JavaParser parser(
		std::make_shared<ParserClientImpl>(storage.get()), std::make_shared<IndexerStateInfo>());
	std::shared_ptr<IndexerCommandJava> command = std::make_shared<IndexerCommandJava>(
		sourceFilePath, L"12", classpath);

	TimeStamp startTime = TimeStamp::now();
	parser.buildIndex(command);
	duration += TimeStamp::now().deltaMS(startTime);

	return TextAccess::createFromLines(TestStorage::create(storage)->m_lines);
}

void processSourceFile(
	const std::string& projectName,
	const utility::file::FilePath& sourceFilePath,
	const std::vector<utility::file::FilePath>& classpath)
{
	const utility::file::FilePath projectDataRoot = utility::file::FilePath("data/JavaIndexSampleProjectsTestSuite/" + projectName);
	const utility::file::FilePath projectDataSrcRoot = projectDataRoot.getConcatenated(L"src");
	const utility::file::FilePath projectDataExpectedOutputRoot = projectDataRoot.getConcatenated(
		L"expected_output");

	std::shared_ptr<TextAccess> output = parseCode(
		projectDataSrcRoot.getConcatenated(sourceFilePath), projectDataSrcRoot, classpath);

	const utility::file::FilePath expectedOutputFilePath = projectDataExpectedOutputRoot.getConcatenated(
		utility::replace(sourceFilePath.withoutExtension().wstr() + L".txt", L"/", L"_"));
	if (updateExpectedOutput || !expectedOutputFilePath.exists())
	{
		std::ofstream expectedOutputFile;
		expectedOutputFile.open(expectedOutputFilePath.str());
		expectedOutputFile << output->getText();
		expectedOutputFile.close();
	}
	else
	{
		std::shared_ptr<TextAccess> expectedOutput = TextAccess::createFromFile(
			expectedOutputFilePath);
		REQUIRE_MESSAGE(
			("Output does not match the expected line count for file " + sourceFilePath.str() +
			 " in project " + projectName + ". Output was: " + output->getText())
				.c_str(),
			expectedOutput->getLineCount() == output->getLineCount());
		if (expectedOutput->getLineCount() == output->getLineCount())
		{
			for (unsigned int i = 1; i <= expectedOutput->getLineCount(); i++)
			{
				REQUIRE(expectedOutput->getLine(i) == output->getLine(i));
			}
		}
	}
}

void processSourceFiles(
	const std::string& projectName,
	const std::vector<utility::file::FilePath>& sourceFilePaths,
	const std::vector<utility::file::FilePath>& classpath)
{
	duration = 0;
	for (const utility::file::FilePath& filePath: sourceFilePaths)
	{
		processSourceFile(projectName, filePath, classpath);
	}
	if (trackTime)
	{
		const utility::file::FilePath projectDataRoot =
			utility::file::FilePath("data/JavaIndexSampleProjectsTestSuite/" + projectName).makeAbsolute();

		std::ofstream outfile;
		outfile.open(
			utility::file::FilePath(projectDataRoot.str() + "/" + projectName + ".timing").str(),
			std::ios_base::app);
		outfile << TimeStamp::now().toString() << " - " << duration << " ms\n";
		outfile.close();
	}
}
}	 // namespace

TEST_CASE("java sample parser can setup environment factory")
{
	std::vector<utility::file::FilePath> javaPaths = utility::getJavaRuntimePathDetector()->getPaths();
	if (!javaPaths.empty())
	{
		ApplicationSettings::getInstance()->setJavaPath(javaPaths[0]);
	}

	setupJavaEnvironmentFactory();

	// if this one fails, maybe your java_path in the test settings is wrong.
	REQUIRE(JavaEnvironmentFactory::getInstance().use_count() >= 1);
}

TEST_CASE("index javasymbolsolver 0 6 0 project")
{
	const std::vector<utility::file::FilePath>& classpath = {
		utility::file::FilePath(L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/lib/guava-21.0.jar")
			.makeAbsolute(),
		utility::file::FilePath(L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/lib/"
				 L"javaparser-core-3.3.0.jar")
			.makeAbsolute(),
		utility::file::FilePath(
			L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/lib/javaslang-2.0.3.jar")
			.makeAbsolute(),
		utility::file::FilePath(L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/lib/"
				 L"javassist-3.19.0-GA.jar")
			.makeAbsolute(),
		utility::file::FilePath(L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/src/"
				 L"java-symbol-solver-core")
			.makeAbsolute(),
		utility::file::FilePath(L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/src/"
				 L"java-symbol-solver-logic")
			.makeAbsolute(),
		utility::file::FilePath(L"data/JavaIndexSampleProjectsTestSuite/JavaSymbolSolver060/src/"
				 L"java-symbol-solver-model")
			.makeAbsolute()};

	processSourceFiles(
		"JavaSymbolSolver060",
		{utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/"
				  L"SourceFileInfoExtractor.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/core/resolution/"
				  L"Context.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/core/resolution/"
				  L"ContextHelper.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/declarations/common/"
				  L"MethodDeclarationCommonLogic.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparser/"
				  L"Navigator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparser/"
				  L"package-info.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"DefaultVisitorAdapter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"JavaParserFacade.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"JavaParserFactory.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"LambdaArgumentTypePlaceholder.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"package-info.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"TypeExtractor.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"UnsolvedSymbolException.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/AbstractJavaParserContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/AbstractMethodLikeDeclarationContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/AnonymousClassDeclarationContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/CatchClauseContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/ClassOrInterfaceDeclarationContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/CompilationUnitContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/ConstructorContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/ContextHelper.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/EnumDeclarationContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/FieldAccessContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/ForechStatementContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/ForStatementContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/JavaParserTypeDeclarationAdapter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/LambdaExprContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/MethodCallExprContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/MethodContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/StatementContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/SwitchEntryContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"contexts/TryWithResourceContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/DefaultConstructorDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/Helper.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserAnnotationDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserAnonymousClassDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserClassDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserConstructorDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserEnumConstantDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserEnumDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserFieldDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserInterfaceDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserMethodDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserParameterDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserSymbolDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserTypeAdapter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserTypeParameter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarations/JavaParserTypeVariableDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarators/AbstractSymbolDeclarator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarators/FieldSymbolDeclarator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarators/NoSymbolDeclarator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarators/ParameterSymbolDeclarator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javaparsermodel/"
				  L"declarators/VariableSymbolDeclarator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistClassDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistConstructorDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistEnumDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistFactory.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistFieldDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistInterfaceDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistMethodDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistParameterDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistTypeDeclarationAdapter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistTypeParameter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"JavassistUtils.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/javassistmodel/"
				  L"package-info.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"LazyType.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"ReferenceTypeImpl.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"MyObjectProvider.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"package-info.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionClassAdapter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionClassDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionConstructorDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionEnumDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionFactory.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionFieldDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionInterfaceDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionMethodDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionMethodResolutionLogic.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionParameterDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"ReflectionTypeParameter.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"comparators/ClassComparator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"comparators/MethodComparator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/reflectionmodel/"
				  L"comparators/ParameterComparator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"ConstructorResolutionLogic.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"MethodResolutionLogic.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"SymbolDeclarator.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"SymbolSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"typesolvers/CombinedTypeSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"typesolvers/JarTypeSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"typesolvers/JavaParserTypeSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"typesolvers/MemoryTypeSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-core/com/github/javaparser/symbolsolver/resolution/"
				  L"typesolvers/ReflectionTypeSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"AbstractClassDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"AbstractTypeDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"ConfilictingGenericTypesException.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"FunctionalInterfaceLogic.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"InferenceContext.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"InferenceVariableType.java"),
		 utility::file::FilePath(L"java-symbol-solver-logic/com/github/javaparser/symbolsolver/logic/"
				  L"ObjectProvider.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"AccessLevel.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"AnnotationDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"ClassDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"ConstructorDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"Declaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"EnumDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"FieldDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"HasAccessLevel.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"InterfaceDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"MethodAmbiguityException.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"MethodDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"MethodLikeDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"ParameterDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"ReferenceTypeDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"TypeDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"TypeParameterDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"TypeParametrizable.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/declarations/"
				  L"ValueDeclaration.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/methods/"
				  L"MethodUsage.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/resolution/"
				  L"SymbolReference.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/resolution/"
				  L"TypeSolver.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/resolution/"
				  L"UnsolvedSymbolException.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/resolution/"
				  L"Value.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"ArrayType.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"LambdaConstraintType.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"NullType.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"PrimitiveType.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"ReferenceType.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"Type.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"TypeTransformer.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"TypeVariable.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"VoidType.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"Wildcard.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"parametrization/TypeParametersMap.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"parametrization/TypeParameterValueProvider.java"),
		 utility::file::FilePath(L"java-symbol-solver-model/com/github/javaparser/symbolsolver/model/typesystem/"
				  L"parametrization/TypeParametrized.java")},
		classpath);
}

#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE
