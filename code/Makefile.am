#
# Makefile.am -- build
#
# (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
#
EXTRA_DIST = configureit

bin_PROGRAMS = optimtest
pkglib_LTLIBRARIES = prob1.la prob2.la prob3.la

prob1_la_LDFLAGS = -module
prob1_la_SOURCES = prob1.c

prob2_la_LDFLAGS = -module
prob2_la_SOURCES = prob2.c

prob3_la_LDFLAGS = -module
prob3_la_SOURCES = prob3.c

optimtest_SOURCES = test.c optim.c sa.c

test-prob1: optimtest prob1.la
	./optimtest -l .libs/prob1.0.so -s prob1

test-prob2: optimtest prob2.la
	./optimtest -l .libs/prob2.0.so -s prob2

test-prob3: optimtest prob3.la
	./optimtest -l .libs/prob3.0.so -s prob3
