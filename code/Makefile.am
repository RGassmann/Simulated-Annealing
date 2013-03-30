#
# Makefile.am -- build
#
# (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
#
EXTRA_DIST = configureit

bin_PROGRAMS = optimtest
pkglib_LTLIBRARIES = prob1.la prob2.la prob3.la goldsteinprice.la beale.la booth.la bulkinN6.la easom.la matyas.la three_hump_camel.la

prob1_la_LDFLAGS = -module
prob1_la_SOURCES = prob1.c

prob2_la_LDFLAGS = -module
prob2_la_SOURCES = prob2.c

prob3_la_LDFLAGS = -module
prob3_la_SOURCES = prob3.c

goldsteinprice_la_LDFLAGS = -module
goldsteinprice_la_SOURCES = goldsteinprice.c

beale_la_LDFLAGS = -module
beale_la_SOURCES = beale.c

booth_la_LDFLAGS = -module
booth_la_SOURCES = booth.c

bulkinN6_la_LDFLAGS = -module
bulkinN6_la_SOURCES = bulkinN6.c

easom_la_LDFLAGS = -module
easom_la_SOURCES = easom.c

matyas_la_LDFLAGS = -module
matyas_la_SOURCES = matyas.c

three_hump_camel_la_LDFLAGS = -module
three_hump_camel_la_SOURCES = three_hump_camel.c

optimtest_SOURCES = test.c optim.c sa.c

test-prob1: optimtest prob1.la
	./optimtest -l .libs/prob1.0.so -s prob1

test-prob2: optimtest prob2.la
	./optimtest -l .libs/prob2.0.so -s prob2

test-prob3: optimtest prob3.la
	./optimtest -l .libs/prob3.0.so -s prob3

test-goldsteinprice: optimtest goldsteinprice.la
	./optimtest -l .libs/goldsteinprice.0.so -s goldsteinprice
	
test-beale: optimtest beale.la
	./optimtest -l .libs/beale.0.so -s beale

test-booth: optimtest booth.la
	./optimtest -l .libs/booth.0.so -s booth

test-bulkinN6: optimtest bulkinN6.la
	./optimtest -l .libs/bulkinN6.0.so -s bulkinN6


test-easom: optimtest easom.la
	./optimtest -l .libs/easom.0.so -s easom

test-matyas: optimtest matyas.la
	./optimtest -l .libs/matyas.0.so -s matyas

test-three_hump_camel: optimtest three_hump_camel.la
	./optimtest -l .libs/three_hump_camel.0.so -s three_hump_camel