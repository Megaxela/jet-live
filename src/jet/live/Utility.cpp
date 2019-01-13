
#include "Utility.hpp"
#include <iomanip>
#include <process.hpp>
#include <sstream>
#include <whereami.h>
#include "jet/live/LiveContext.hpp"

namespace jet
{
    std::string getExecutablePath()
    {
        std::string pathString;
        auto pathLength = static_cast<size_t>(wai_getExecutablePath(nullptr, 0, nullptr));
        pathString.resize(pathLength);
        wai_getExecutablePath(const_cast<char*>(pathString.data()), static_cast<int>(pathLength), nullptr);
        return pathString;
    }

    std::string toString(const ElfContext& context, const ElfSymbol& elfSymbol)
    {
        std::string s;

        switch (elfSymbol.type) {
            case ElfSymbolType::kNo: s += "No\t\t\t"; break;
            case ElfSymbolType::kObject: s += "Object\t\t"; break;
            case ElfSymbolType::kFunction: s += "Function\t\t"; break;
            case ElfSymbolType::kSection: s += "Section\t\t"; break;
            case ElfSymbolType::kFile: s += "File\t\t"; break;
            case ElfSymbolType::kCommonObject: s += "CommonObject\t"; break;
            case ElfSymbolType::kThreadLocalObject: s += "ThreadLocalObject\t"; break;
            case ElfSymbolType::kIndirect: s += "Indirect\t\t"; break;
        }

        s += "| ";
        switch (elfSymbol.binding) {
            case ElfSymbolBinding::kLocal: s += "Local\t"; break;
            case ElfSymbolBinding::kGlobal: s += "Global\t"; break;
            case ElfSymbolBinding::kWeak: s += "Weak\t"; break;
            case ElfSymbolBinding::kUnique: s += "Unique\t"; break;
        }

        s += "| ";
        switch (elfSymbol.visibility) {
            case ElfSymbolVisibility::kDefault: s += "Default\t"; break;
            case ElfSymbolVisibility::kInternal: s += "Internal\t"; break;
            case ElfSymbolVisibility::kHidden: s += "Hidden\t"; break;
            case ElfSymbolVisibility::kProtected: s += "Protected\t"; break;
        }

        s += "| ";
        const auto& sectionName1 = context.sectionNames.size() <= elfSymbol.sectionIndex ?
                                       std::string("?") :
                                       context.sectionNames[elfSymbol.sectionIndex];
        s += std::to_string(elfSymbol.sectionIndex) + "(" + sectionName1 + ")\t| ";
        s += "ADDR " + std::to_string(elfSymbol.virtualAddress) + "\t| ";
        s += "SIZE " + std::to_string(elfSymbol.size) + "\t| ";
        s += elfSymbol.name;

        return s;
    }

    std::string toString(const MachoContext& context, const MachoSymbol& machoSymbol)
    {
        std::string s;

        switch (machoSymbol.type) {
            case MachoSymbolType::kUndefined: s += "Undefined\t\t"; break;
            case MachoSymbolType::kAbsolute: s += "Absolute\t\t"; break;
            case MachoSymbolType::kSection: s += "Section\t\t"; break;
            case MachoSymbolType::kPreboundUndefined: s += "PreboundUndefined\t"; break;
            case MachoSymbolType::kIndirect: s += "Indirect\t\t"; break;

            case MachoSymbolType::kGSYM: s += "GSYM\t"; break;
            case MachoSymbolType::kFNAME: s += "FNAME\t"; break;
            case MachoSymbolType::kFUN: s += "FUN\t"; break;
            case MachoSymbolType::kSTSYM: s += "STSYM\t"; break;
            case MachoSymbolType::kLCSYM: s += "LCSYM\t"; break;
            case MachoSymbolType::kBNSYM: s += "BNSYM\t"; break;
            case MachoSymbolType::kAST: s += "AST\t"; break;
            case MachoSymbolType::kOPT: s += "OPT\t"; break;
            case MachoSymbolType::kRSYM: s += "RSYM\t"; break;
            case MachoSymbolType::kSLINE: s += "SLINE\t"; break;
            case MachoSymbolType::kENSYM: s += "ENSYM\t"; break;
            case MachoSymbolType::kSSYM: s += "SSYM\t"; break;
            case MachoSymbolType::kSO: s += "SO\t\t"; break;
            case MachoSymbolType::kOSO: s += "OSO\t"; break;
            case MachoSymbolType::kLSYM: s += "LSYM\t"; break;
            case MachoSymbolType::kBINCL: s += "BINCL\t"; break;
            case MachoSymbolType::kSOL: s += "SOL\t"; break;
            case MachoSymbolType::kPARAMS: s += "PARAMS\t"; break;
            case MachoSymbolType::kVERSION: s += "VERSION\t"; break;
            case MachoSymbolType::kOLEVEL: s += "OLEVEL\t"; break;
            case MachoSymbolType::kPSYM: s += "PSYM\t"; break;
            case MachoSymbolType::kEINCL: s += "EINCL\t"; break;
            case MachoSymbolType::kENTRY: s += "ENTRY\t"; break;
            case MachoSymbolType::kLBRAC: s += "LBRAC\t"; break;
            case MachoSymbolType::kEXCL: s += "EXCL\t"; break;
            case MachoSymbolType::kRBRAC: s += "RBRAC\t"; break;
            case MachoSymbolType::kBCOMM: s += "BCOMM\t"; break;
            case MachoSymbolType::kECOMM: s += "ECOMM\t"; break;
            case MachoSymbolType::kECOML: s += "ECOML\t"; break;
            case MachoSymbolType::kLENG: s += "LENG\t"; break;
            case MachoSymbolType::kPC: s += "PC\t\t"; break;
        }

        s += "| ";
        switch (machoSymbol.referenceType) {
            case MachoSymbolReferenceType::kUndefinedNonLazy: s += "UndefinedNonLazy\t\t"; break;
            case MachoSymbolReferenceType::kUndefinedLazy: s += "UndefinedLazy\t\t"; break;
            case MachoSymbolReferenceType::kDefined: s += "Defined\t\t\t"; break;
            case MachoSymbolReferenceType::kPrivateDefined: s += "PrivateDefined\t\t"; break;
            case MachoSymbolReferenceType::kPrivateUndefinedNonLazy: s += "PrivateUndefinedNonLazy\t"; break;
            case MachoSymbolReferenceType::kPrivateUndefinedLazy: s += "PrivateUndefinedLazy\t"; break;
        };

        s += "| ";
        s += "RD " + std::to_string(static_cast<int>(machoSymbol.referencedDynamically)) + "\t| ";
        s += "DD " + std::to_string(static_cast<int>(machoSymbol.descDiscarded)) + "\t| ";
        s += "WR " + std::to_string(static_cast<int>(machoSymbol.weakRef)) + "\t| ";
        s += "WD " + std::to_string(static_cast<int>(machoSymbol.weakDef)) + "\t| ";
        s += "PE " + std::to_string(static_cast<int>(machoSymbol.privateExternal)) + "\t| ";
        s += "E " + std::to_string(static_cast<int>(machoSymbol.external)) + "\t| ";
        const auto& sectionName1 = context.sectionNames.size() <= machoSymbol.sectionIndex ?
                                       std::string("?") :
                                       context.sectionNames[machoSymbol.sectionIndex];
        s += std::to_string(machoSymbol.sectionIndex) + "(" + sectionName1 + ")\t| ";
        s += "ADDR " + std::to_string(machoSymbol.virtualAddress) + "\t| ";
        s += "SIZE " + std::to_string(machoSymbol.size) + "\t| ";
        s += machoSymbol.name;

        return s;
    }

    std::string toString(LinkerType linkerType)
    {
        switch (linkerType) {
            case LinkerType::kLLVM_lld: return "LLVM lld";
            case LinkerType::kGNU_ld: return "GNU ld";
            case LinkerType::kApple_ld: return "Apple ld";
            default: return "Unknown";
        }
    }

    std::string createLinkCommand(const std::string& libName,
        const std::string& compilerPath,
        uintptr_t baseAddress,
        LinkerType linkerType,
        const std::vector<std::string>& objectFilePaths)
    {
        std::string res = compilerPath + " -fPIC -shared -g";
        std::stringstream ss;
        ss << std::hex << baseAddress;

        switch (linkerType) {
            case LinkerType::kGNU_ld: {
                res.append(" -Wl,-Ttext-segment=0x")
                    .append(ss.str())
                    .append(" -Wl,-export-dynamic")
                    .append(" -Wl,-soname,")
                    .append(libName);
                break;
            }
            case LinkerType::kLLVM_lld: {
                res.append(" -Wl,--image-base=0x")
                    .append(ss.str())
                    .append(" -Wl,-export-dynamic")
                    .append(" -Wl,-soname,")
                    .append(libName);
                break;
            }
            case LinkerType::kApple_ld: {
                res.append(" -Wl,-image_base=0x")
                    .append(ss.str())
                    .append(" -Wl,-export_dynamic")
                    .append(" -Wl,-install_name,")
                    .append(libName)
                    .append(" -undefined dynamic_lookup");
                break;
            }
            case LinkerType::kUnknown: {
                return "INVALID LINKER TYPE";
                break;
            }
        }

        res.append(" -o ").append(libName).append(" ");
        for (const auto& oFile : objectFilePaths) {
            res.append("\"" + oFile + "\" ");
        }

        return res;
    }

    uintptr_t findPrefferedBaseAddressForLibrary(const std::vector<std::string>& objectFilePaths)
    {
        // TODO: implement me
        (void)objectFilePaths;
        return 0;
    }

    LinkerType getSystemLinkerType(const LiveContext* context)
    {
        std::string procOut;
        std::string procError;
        auto status = TinyProcessLib::Process{"ld -v",
            "",
            [&procOut](const char* bytes, size_t n) { procOut += std::string(bytes, n); },
            [&procError](const char* bytes, size_t n) { procError += std::string(bytes, n); }}
                          .get_exit_status();
        if (status != 0) {
            context->listener->onLog(LogSeverity::kError, "'ld -v' failed: \n" + procOut + "\n" + procError);
            return LinkerType::kUnknown;
        }

        if (procOut.find("LLD") != std::string::npos) {
            return LinkerType::kLLVM_lld;
        } else if (procOut.find("GNU") != std::string::npos) {
            return LinkerType::kGNU_ld;
        } else if (procError.find("PROGRAM:ld") != std::string::npos) {
            // For some reason apple ld prints this info to stderr
            return LinkerType::kApple_ld;
        }

        context->listener->onLog(LogSeverity::kError, "Cannot find out linker type: \n" + procOut);
        return LinkerType::kUnknown;
    }
}
