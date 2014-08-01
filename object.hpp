#ifndef OBJECT
#define OBJECT

typedef struct
{
	Model *model;
	vec3 position;
} Object;

typedef struct objectNode
{
	Object *object;
	objectNode *next;	
} ObjectNode;
#endif

