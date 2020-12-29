# argparse
A slimline C++ class for parsing command-line arguments, with an interface similar to python's class of the same name.

## Usage
An example says it best:

    #include "argparse.hpp"

    int main(int argc, const char** argv) {

        // make a new ArgumentParser
        argparse::ArgumentParser parser("app description");

        // add some arguments to search for
        parser.add_argument("-a");
        parser.add_argument("-c", "--cactus", 1);
        parser.add_argument("-o", "--optional");
        parser.add_argument("-r", "--required", 1, false);
        parser.add_argument("-w", "--with_help", 1, true, "information");
        parser.add_argument("--five", 5);
        parser.add_argument("--atleast", '+');
        parser.add_argument("--any", '*');
        parser.add_FinalArgument("output");

        // parse the command-line arguments - throws if invalid format
        parser.parse_args(argc, argv);

        // if we get here, the configuration is valid
        int cactus = parser.retrieve<int>("cactus");
        return cactus;
    }

If the supplied format is incorrect or we specified `-h` or `--help`, the program shows a usage string then exit:

    Usage: 
    app description

    app_name --required REQUIRED [--help] [-a] [--cactus CACTUS] [--optional] [--with_help WITH_HELP] [--five FIVE FIVE FIVE ...] [--atleast ATLEAST [ATLEAST...]] [--any [ANY ANY...]] OUTPUT
    
    required arguments:
    --required | 
    
    optional arguments:
    --help | show this help message and exit
    -a | 
    --cactus | 
    --optional | 
    --with_help | information
    --five | 
    --atleast | 
    --any |

## Compiling
Just grab the `argparse.hpp` header and go! The `ArgumentParser` is the only definition in `argparse.hpp`. Dependent classes are nested within `ArgumentParser`.

It is recommended to include `argparse.hpp` only in your `main.cpp`, otherwise template linking issues may arise

## Format
### specifier
Arguments can be specified in a number of formats. They can have single character short names (only 1 character) prefixed with a single '-':

    -b

or long name prefixed with '--':

    --banana

### number
The number of expected inputs trailing an argument can also be specified. This comes in two flavours:
1. fixed number arguments
2. variable number arguments

Fixed number arguments are simply specified with an integer which is `0` or greater. If that exact number of inputs trailing the argument is not found, the parser will fail with a `std::invalid_argument` exception. If the number is `1`, the input is stored as a string. If the number is greater than `1`, the input is stored as a vector of strings.

Variable number arguments allow for an undetermined number of inputs trailing an argument. The parser will attempt to consume as many arguments as possible until the next valid argument is encountered. There are two types of variable argument specifiers, and they use the same syntax as regular expressions:
1. `'+'` matches one or more inputs
2. `'*'` matches zero or more inputs

In both cases, the output is stored as a vector of strings. If the number of inputs is not specified, it defaults to `0`.

### required/optional
Arguments can be marked as either required or optional. All required arguments must appear before any optional arguments in the command-line input.

### final
Often UNIX command-line tools have an un-named final argument that collects all remaining inputs. The name that these inputs map to internally can be specified using the `add_FinalArgument()` method of `ArgumentParser`. Along with its name, you can also specify the number of inputs to parse. Since it is un-named however, there are a number of restrictions:
1. The final argument can always require a fixed number of inputs
2. If a fixed number of inputs is specified, it must be `1` or greater
3. The final argument can only take the `'+'` specifier if an argument with variadic number of inputs has not already been specified. This restiction exists because arguments do not have a fixed ordering and a variadic argument just before the final (un-named) argument will consume all of the reminaing arguments unless the final argument requires a fixed number of inputs

## Retrieving
Inputs to an argument can be retrieved with the `retrieve()` method of `ArgumentParser`. Importantly, if the inputs are parsed as an array, they must be retrieved as an array. Failure to do so will result in a `std::bad_cast` exception. 

Arguments can also be cast to other types as long as the cast is trivial. For instance, we could retrieve the array of strings from the '--five' argument as an array of ints:

    vector<int> five = parser.retrieve<vector<int> >("five");

or convert the required argument to a float:

    float req = parser.retrieve<float>("r");

## Method Summary
|        name         |      function      |
|---------------------|--------------------|
|  ArgumentParser()   | default constructor 
|   useExceptions()   | if true, parsing errors throw exceptions rather than printing to stderr and exiting
|      appName()      | set the name of the application
|   add_argument()    | specify an argument to search for
| add_FinalArgument() | specify a final un-named argument
|ignoreFirstArgument()| don't parse the first argument (usually the caller name on UNIX)
|    parse_args()     | invoke the parser on a `char**` array
|     retrieve()      | retrieve a set of inputs for an argument
|       usage()       | return a formatted usage string
|       empty()       | check if the set of specified arguments isempty
|       clear()       | clear all specified arguments
|      exists()       | check if an argument has been found
|    gotArguemnt()    | check if an argument is provided by the user
