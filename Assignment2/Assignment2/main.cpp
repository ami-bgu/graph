#include <stdio.h>
#include "ScenePainter.h"
#include "SceneFileParser.h"

int main(int  argc, char** argv)
{
	if (argc < 2){
		printf("Please specify a filename. \n Exiting..");
		getc(stdin);
		return 0;
	}
	SceneManager manager;
	SceneFileParser::parse(manager, argv[1]);
	Resolution res = manager.getResolution();

	GLubyte* pic = new GLubyte[res.width*res.height*3];

	manager.render(pic);
	ScenePainter painter;
	painter.paintToScreen(pic, res);

	delete[] pic;
}