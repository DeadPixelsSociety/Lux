# Lux
Game for the Year of Light

## Compilation
### With mouse controler

	mkdir build
	cd build
	cmake ../src
	make 
	make install

### With the lightpad controler

	mkdir build
	cd build
	cmake ../src -DLUX_MOUSE_CONTROL=OFF
	make 
	make install
