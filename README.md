# Bliss

A library to make cli program easy

## Build and Run

```
$ make
$ make example -s
$ ./bin/example
exampleApp | example of bliss

Usage:
		exampleApp [OPTIONS] [SUBCOMMANDS]

Options:
		-h --hello : print 'HELLO BLISS OPTION'

Subcommands:
		hello : print 'HELLO BLISS SUBCOMMAND'
$ ./bin/example --hello
HELLO BLISS OPTION
$ ./bin/example hello
HELLO BLISS SUBCOMMAND
$ ./bin/example blablabla
NOT FOUND SUBCOMMAND: blablabla
$ ./bin/example --blablabla
NOT FOUND OPTION: --blablabla

```

## License

Bliss is primarily distributed under the terms of MIT license.

See [LICENSE](/LICENSE) for details.

