CC := xtensa-esp32-elf-gcc
CFLAGS := -I$(IDF_PATH)/components -DESP32
LDFLAGS := -L$(IDF_PATH)/lib -lfreertos -ldriver -lesp_system -T esp32.ld

ESP32_OBJ := cmatrix.o cmatrix_esp32.o

cmatrix_esp32: $(ESP32_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

cmatrix.o: cmatrix.c
	$(CC) $(CFLAGS) -c $< -o $@

cmatrix_esp32.o: cmatrix_esp32.c
	$(CC) $(CFLAGS) -c $< -o $@
