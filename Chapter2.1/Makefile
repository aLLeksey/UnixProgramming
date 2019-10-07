file = od
all: $(file)

$(file): $(file).c
	if gcc  $(file).c -o $(file); then \
echo "success";\
else \
echo "failure"; \
fi

clean:
	rm -rf $(file)
