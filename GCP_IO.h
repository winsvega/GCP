#ifndef GCP_IOH
#define GCP_IOH
#include <fstream>
#include <sstream>
#include <string.h>
#include "SDL.h"

namespace gcp
{
	//ÐÀÁÁÎÒÀ Ñ ÂÂÎÄÎÌ ÂÛÂÎÄÎÌ
	class GPC_IO_ERROR
	{
	};

	class GCP_IO
	{
	private:
		std::fstream fs;
		int _iMode;
		bool _isClosed;
	public:
		SDL_RWops *io;
		const static int GCP_IO_INPUT = 0;
		const static int GCP_IO_OUTPUT = 1;
		const static int GCP_IO_OUTPUTTXT = 2;
		const static int GCP_IO_INPUTTXT = 3;
		GCP_IO(std::string filename, int mode)
		{
			_isClosed = false;
			switch (mode)
			{
			case GCP_IO_INPUT:
				io = SDL_RWFromFile(filename.c_str(), "rb"); break;
			case GCP_IO_OUTPUT:
				io = SDL_RWFromFile(filename.c_str(), "wb"); break;
			case GCP_IO_OUTPUTTXT:
				io = SDL_RWFromFile(filename.c_str(), "w"); break;
			case GCP_IO_INPUTTXT:
				io = SDL_RWFromFile(filename.c_str(), "r"); break;
			}
			_iMode = mode;
		}

		~GCP_IO()
		{
			if (!_isClosed)
				io->close(io);
		}

		void read(void *type, size_t size, int count = 1)
		{
			io->read(io, type, size, count);
		}
		void write(const void *type, size_t size, int count = 1)
		{
			io->write(io, type, size, count);
		}

		int readInt()
		{
			int value;
			readInt(&value);
			return value;
		}

		unsigned int readUInt()
		{
			unsigned int value;
			readInt(&value);
			return value;
		}

		double readDouble()
		{
			double value;
			readDouble(&value);
			return value;
		}

		std::string readString()
		{
			std::string value;
			readString(&value);
			return value;
		}

		void readInt(int *value)
		{
			io->read(io, value, sizeof(int), 1);
		}

		void readInt(unsigned int *value)
		{
			io->read(io, value, sizeof(unsigned int), 1);
		}

		void readDouble(double *value)
		{
			io->read(io, value, sizeof(double), 1);
		}

		void readString(std::string *value)
		{
			*value = "";
			if (GCP_IO_INPUTTXT == _iMode)
			{
				char str = 0;
				io->read(io, &str, sizeof(str), 1);
				while (str != 10 && str != 0) //line separators, ending
				{
					*value += str;
					io->read(io, &str, sizeof(str), 1);
				}
				return;
			}
			else
			{
				char str[256];
				io->read(io, &str, sizeof(str), 1);
				*value = str;
			}
		}

		void writeInt(int value)
		{
			io->write(io, &value, sizeof(int), 1);
		}

		void writeDouble(double value)
		{
			io->write(io, &value, sizeof(double), 1);

		}
		void writeString(std::string value)
		{
			char str[256];
			strncpy(str, value.c_str(), 255);

			if (GCP_IO_OUTPUTTXT == _iMode)
			{
				size_t len = SDL_strlen(str);
				if (SDL_RWwrite(io, str, 1, len) != len)
					throw GPC_IO_ERROR();
			}
			else
				io->write(io, &str, sizeof(str), 1);
		}

		void writeln()
		{
			char str = '\n';
			SDL_RWwrite(io, &str, 1, 1);
		}

		void close()
		{
			if (!_isClosed)
				io->close(io);
			_isClosed = true;
		}
	};
}
#endif
