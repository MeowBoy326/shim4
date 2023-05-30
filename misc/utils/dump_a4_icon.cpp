#include "shim4/shim4.h"

using namespace noo;

int main(int argc, char **argv)
{
	try {
		shim::static_start_all();

		shim::argc = argc+1;
		shim::argv = new char *[shim::argc];
		for (int i = 0; i < shim::argc-1; i++) {
			shim::argv[i] = new char[strlen(argv[i])+1];
			strcpy(shim::argv[i], argv[i]);
		}
		shim::argv[shim::argc-1] = new char[strlen("-fullscreen")+1];
		strcpy(shim::argv[shim::argc-1], "-fullscreen");
		shim::hide_window = true;
		shim::use_cwd = true;
		shim::error_level = 3;
		shim::log_tags = false;

		shim::start_all(100, 100, false, 100, 100);

		if (argc < 2) {
			util::infomsg("Usage: %s <image.tga>\n", argv[0]);
			return 0;
		}

		gfx::Image::premultiply_alpha = false;
		gfx::Image::keep_data = true;
		gfx::Image::save_rgba = true;

		gfx::Image *img = new gfx::Image(argv[1], false, true);

		unsigned char *data = img->get_loaded_data();

		printf("unsigned long icon_data[] = {\n");
		printf("\t0x%x,\n", img->size.w);
		printf("\t0x%x,\n", img->size.h);

		for (int y = 0; y < img->size.h; y++) {
			unsigned char *p = data + y * (img->size.w * 4);
			for (int x = 0; x < img->size.w; x++) {
				int r = p[0];
				int g = p[1];
				int b = p[2];
				int a = p[3];
				printf("\t0x%x", ((a << 24) | (r << 16) | (g << 8) | b));
				p += 4;
				if (x < img->size.w-1 || y < img->size.h-1) {
					printf(",\n");
				}
			}
		}

		printf("\n};\n");

		delete img;

		shim::end_all();

		shim::static_end();
	}
	catch (util::Error e) {
		util::errormsg("Fatal error: %s\n", e.error_message.c_str());
	}

	return 0;
}
