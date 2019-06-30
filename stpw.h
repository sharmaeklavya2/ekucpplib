#ifndef _INC_EKU_STPW
#define _INC_EKU_STPW

namespace eku
{
	template<class typ>
	class stpw
	{
		short st;	//status: 0-off,1-on,2-pause
		typ str,end,dur;
	public:
		stpw():str(0),end(0),st(0),dur(0){}
		void update(){if(st==typ(1)){end=typ(clock());dur+=end-str;str=typ(clock());}}
		void start(){if(st==typ(0))dur=typ(0);str=typ(clock());st=typ(1);}
		void pause(){update();if(st==typ(1))st=typ(2);}
		void stop(){update();st=typ(0);}
		typ showms(){update();return dur;}	//show as milliseconds
		float shows(){update();return float(dur)/1000;}	//show as seconds
	};
}

#endif	//_INC_EKU_STPW