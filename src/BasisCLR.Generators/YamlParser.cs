using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using YamlDotNet.Serialization;
using YamlDotNet.Serialization.NamingConventions;

namespace BasisCLR.Generators
{
    internal class ParameterList
    {
        public List<Parameter> Parameters { get; set; } = new List<Parameter>();
    }

    internal class Parameter
    {        
        public string Name { get; set; } = string.Empty;
        public string Type { get; set; } = string.Empty;
        public string Default { get; set; } = string.Empty;
        public string Comment { get; set; } = string.Empty;

        public override string ToString()
        {
            var output = $"{this.Type} {this.Name}";
            if(!string.IsNullOrEmpty(this.Default))
            {
                output += $"  = {this.Default}";
            }

            if (!string.IsNullOrEmpty(this.Comment))
            {
                output += $" // {this.Comment}";
            }
            return output;
        }
    }

    internal class YamlParser
    {
        public static ParameterList Parse(string filename)
        {
            var deserializer = new DeserializerBuilder()
                .WithNamingConvention(CamelCaseNamingConvention.Instance)
                .Build();

            var input = File.ReadAllText(filename);
            var parameters = deserializer.Deserialize<ParameterList>(input);

            return parameters;
        }
    }
}
