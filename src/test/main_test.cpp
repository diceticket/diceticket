#include <iostream>
#include <stdio.h>
#include <getopt.h>

//#define TEST_TIME                 1


static struct CmdLine
{
	int save, debug, skip, jump, tri, ep;
	float pixel_unit, shift;
	char path[256], input[256];

	CmdLine(): save(0), debug(0), skip(0), jump(-1), tri(0), ep(0),
			pixel_unit(-1), shift(250)
	{
		path[0] = input[0] = 0;
	}
}line;

static void print_help();
static int ParseCmdLine(CmdLine &line, int argc, char* argv[]);


int main(int argc, char* argv[])
{
	LOGI("%s", LaneTrack::GetVersion());

	int res = ParseCmdLine(line, argc, argv);
	if( res < 0 )
		return STEREO_ERR_ARG;
	res = STEREO_SUCCEED;

	return res;
}


static int ParseCmdLine(CmdLine &line, int argc, char* argv[])
{
	static const char *shortopts = ":"
			"e:" // image file extension
			"l:" // left image file pattern
			"p:" // image files path and params save path
			"r:" // right image file pattern
			"i:" // source video file

			"f:" // shift
			"u:" // bird view scale
			"k:" // skip frames
			"j:" // jump

			"D"  // debug
			"R"  // image is reactive
			"E"  // end ponit
			"T"  // Tachograph video model
			"S"  // save result

			"h"  // print help message
			"v";  // paint version

	struct option longopts[] = {
			{"ext", required_argument, NULL, 'e'},
			{"left", required_argument, NULL, 'l'},
			{"path", required_argument, NULL, 'p'},
			{"right", required_argument, NULL, 'r'},
			{"input", required_argument, NULL, 'i'},

			{"shift", required_argument, NULL, 'f'},
			{"unit", required_argument, NULL, 'u'},
			{"skip", required_argument, NULL, 'k'},
			{"jump", required_argument, NULL, 'j'},

			{"debug", no_argument, NULL, 'D'},
			{"rectify", no_argument, NULL, 'R'},
			{"tri", no_argument, NULL, 'T'},
			{"endpoint", no_argument, NULL, 'E'},
			{"save", no_argument, NULL, 'S'},

			{"help", no_argument, NULL, 'h'},
			{"version", no_argument, NULL, 'v'},
			{0, 0, 0, 0},
	};
	int res, idx;

	while( (res = getopt_long(argc, argv, shortopts, longopts, &idx)) != -1 )
	{
		switch(res)
		{
		case 'p':
			strcpy(line.path, optarg);
			break;
		case 'e':
			line.search.ext = optarg;
			break;
		case 'l':
			line.search.left_pattern = optarg;
			break;
		case 'r':
			line.search.rght_pattern = optarg;
			break;
		case 'i':
			strcpy(line.input, optarg);
			break;

		case 'f' :
			std::stringstream(optarg) >> line.shift;
			break;
		case 'u' :
			std::stringstream(optarg) >> line.pixel_unit;
			break;
		case 'k':
			std::stringstream(optarg) >> line.skip;
			break;
		case 'j':
			std::stringstream(optarg) >> line.jump;
			break;

		case 'D':
			line.debug = 1;
			break;
		case 'E':
			line.ep = 1;
			break;
		case 'T':
			line.tri = 1;
			break;
		case 'S':
			line.save = 1;
			break;

		case 'h':
			print_help();
			return STEREO_USE_EXIT;
		case 'v':
			std::cout<<LaneTrack::GetVersion()<<std::endl;
			return STEREO_USE_EXIT;

		case ':': case '?': default:
			print_help();
			return STEREO_ERR_ARG;
		}
	}

	return STEREO_SUCCEED;
}

static void print_help()
{
    std::cout<<"Detect Road Lane. \n";

    std::cout<< "\nUsage: "
    		"\t lane [options] [-p path] \n"
    		"\t lane [--help][--version] \n";

    std::cout<< "\nOptions: \n"
    		"  -e, --ext        image file extension.\n"
    		"  -f, --shift      bird view shift y coordinate.\n"
    		"  -h, --help       print help message.\n"
    		"  -i, --input      input source image or video.\n"
    		"  -k, --skip       skip video frames.\n"
    		"  -l, --left       left image file pattern.\n"
    		"  -p, --path       image files path.\n"
    		"  -r, --right      right image file pattern.\n"
    		"  -s, --second     interval seconds.\n"
    		"  -S, --save       save result.\n"
    		"  -T, --tri        Tachograph video model.\n"
    		"  -u, --unit       bird view 1 pixel size, cm/pixel.\n"
    		"  -v, --version    print version and copyright info.\n"
    		<<std::endl;
}

