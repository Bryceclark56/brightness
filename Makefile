brightness: brightness.c
	clang -Wall -Wpedantic -Wextra -Werror -stdlib=musl brightness.c -o brightness
