class pageStruct
{
public:
	int page;
	int block;
	int next;
};

class processStart
{
public:
	int id;
	int start;
	int size;


	
	processStart()
	{
		id=-1;
		start=-1;
		size=-1;
	}
	processStart(const processStart& P)
	{
		id=P.id;
		size=P.size;
		start=P.start;
	}
};