version := --std=c++11

path := conn.c

a.out: $(path)
	g++ $(version) $(path) -o $@ -lmysqlclient
	./$@

.PHONY: clean

clean:
	rm -rf a.out