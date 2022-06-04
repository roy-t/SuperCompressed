

//// TODO

//// read D:\Projects\C#\SuperCompressedDotNet\src\external\basis_universal\encoder\basisu_comp.h 
//// lines 319 to 443

//// See https://aka.ms/new-console-template for more information

using BasisCLR.Generators;
using CommandLine;

Parser.Default.ParseArguments<ExtractOptions, GenerateOptions>(args)
    .WithParsed<ExtractOptions>(e =>
    {
        Console.WriteLine($"Extracting {e.Input}:[{e.From}..{e.To}] to {e.Output}");
        HeaderParser.Parse(e.Input, e.From, e.To);

    })
    .WithParsed<GenerateOptions>(g =>
    {
        YamlParser.Parse(g.Input);
    });

//// Yay raw string literals fancy pancy
//var hello = "";
//var v = 
//    $$""""
//    Hello World
//    Yes baby
//    {rhhreher}
//    """{{hello}}
//        rearlerler'r'q439501"5353"
//    """";


//Console.WriteLine(v);
//Console.WriteLine("Now what");