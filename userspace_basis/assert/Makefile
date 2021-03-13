
MAIN=assert

normal:
	gcc -o ${MAIN} ${MAIN}.c -Wall

disable:
	gcc -o ${MAIN} ${MAIN}.c -Wall -DNDEBUG

clean:
	rm ${MAIN}

test:
	@echo "###test parameter"
	@if ./assert 10; then \
		echo "return value $$?"; \
    else \
		echo "return value $$?"; \
	fi
	@echo "###test assertion successful"
	@if ./assert 10; then \
		echo "return value $$?"; \
    else \
		echo "return value $$?"; \
	fi
	@echo "###test assertion fail"
	@if ./assert 11; then \
		echo "return value $$?"; \
    else \
		echo "return value $$?"; \
	fi
	@echo "###test finish"
