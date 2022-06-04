using CommandLine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasisCLR.Generators
{
    [Verb("extract", HelpText = "Try to extract all fields and types from a C++ header file")]
    internal sealed class ExtractOptions
    {
        [Option('i', "input", Default = "", Required = true, HelpText = "The header file to parse")]
        public string Input { get; set; } = "";

        [Option('o', "output", Default = "", Required = true, HelpText = "The output xml file to generate")]
        public string Output { get; set; } = "";

        [Option('f', "from", Default = 1, Required = false, HelpText = "First line to parse")]
        public int From { get; set; }

        [Option('t', "to", Default = int.MaxValue, Required = false, HelpText = "Last line to parse")]
        public int To { get; set; }
    }

    [Verb("generate", HelpText = "Try to generate source code based on an XML file with fields")]
    internal sealed class GenerateOptions
    {
        [Option('i', "input", Default = "", Required = true, HelpText = "Input xml file to generate from")]
        public string Input { get; set; } = "";

        [Option('o', "output", Default = "", Required = false, HelpText = "The output file to generate")]
        public string Output { get; set; } = "";

        [Option('m', "mode", Default = GenerateMode.Clr, Required = false, HelpText = "The type of file to generate")]
        public GenerateMode Mode { get; set; }

    }

    internal enum GenerateMode
    {
        Clr,
        PlainCpp,
        ClrToPlainCpp,
        PlainCppToBasisu
    }
}
