using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BasisCLR.Generators
{
    internal class HeaderParser
    {
        public static void Parse(string path, int from, int to)
        {
            var parameters = new List<ParameterInfo>();

            var currentLine = 0;
            var text = File.ReadAllText(path).AsSpan();
            foreach(var line in text.EnumerateLines())
            {
                currentLine++;
                if (currentLine < from || currentLine > to) { continue; }
                

                var trimmed = line.Trim();
                if(!CommentParser(trimmed) && trimmed.Length > 0)
                {
                    var ns = ParseNamespace(trimmed);
                    parameters.Add(new ParameterInfo("", new TypeInfo("", ns.ToString())));
                }
            }
        }


        public static bool CommentParser(ReadOnlySpan<char> trimmedLine)
        {
            return trimmedLine.StartsWith("//");
        }

        public static ReadOnlySpan<char> ParseNamespace(ReadOnlySpan<char> trimmedLine)
        {

            var tokens = "";
            for(var i = 0; i < trimmedLine.Length; i++)
            {
                var c = trimmedLine[i];
                if ((char.IsLetterOrDigit(c) || c == '_'))
                {
                    if (!tokens.EndsWith('v'))
                    {
                        tokens += "v";
                    }
                }
                else
                if (char.IsWhiteSpace(c))
                {
                    if (!tokens.EndsWith('w'))
                    {
                        tokens += "w";
                    }
                }
                else
                if (c == ':')
                {
                    if (!tokens.EndsWith(':'))
                    {
                        tokens += ":";
                    }
                }
                else                
                {
                    tokens += '!';
                }

                if (   !tokens.EndsWith("v") 
                    && !tokens.EndsWith("v:") 
                    && !tokens.EndsWith("vw") 
                    && !tokens.EndsWith("vw:") 
                    && !tokens.EndsWith(":w"))
                {
                    if (tokens.Contains(":"))
                    {
                        var slice = trimmedLine.Slice(0, i);
                        var index = slice.LastIndexOf(':') - 1;
                        return slice.Slice(0, index);
                    }
                    break;
                }                
            }

            return new ReadOnlySpan<char>();
        }
    }

    internal record TypeInfo(string Type, string Namespace, bool IsGeneric = false, string GenericTypeArgument = "");
    internal record ParameterInfo(string Name, TypeInfo Type);
}
