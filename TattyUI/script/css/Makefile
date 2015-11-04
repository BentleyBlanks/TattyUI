# -o指定生成的输出文件
# $@代表当前Makefile taget的名称 这里直接作为可执行文件名
# FlexBison-3: Flex-3.l Bison-3.y
# 			bison -d Bison-3.y
# 			flex Flex-3.l
# 			cc -o $@ Bison-3.tab.c lex.yy.c 

# t2CSS:
# 	Flex-6-CSS2.l Bison-3.y
# 	bison -d Bison-4-CSS2.y
# 	flex -o t2CSSLex.c Flex-6-CSS2.l
# 	cc -o $@ t2CSSLex.c

t2CSSBison.cpp t2CSSBison.h: Bison-5-CSS2.y
	bison -d -o $@ $< 

t2CSSLex.cpp: Flex-8-CSS2.l
	flex -o $@ $<

clean:
	rm -f t2CSSBison.h t2CSSBison.cpp
	rm -f t2CSSLex.h t2CSSLex.cpp

# t2CSSParser.cpp: Bison-4-CSS2.y
# 	bison -d -o $@ $^

# t2CSSLex.cpp: Flex-6-CSS2.l t2CSSParser.hpp
# 	flex -o t2CSSLex.cpp 

# cssParser: 
# 	g++ -o $@ t2CSSParser.cpp t2CSSLex.cpp main.cpp

