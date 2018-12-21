#ifndef __LAYERIDINFO_H
#define __LAYERIDINFO_H

inline LPCWSTR GetEnumLayer(unsigned layid)
{
	static const LPCWSTR layers[] =
	{
		/*0*/NULL,
		/*1*/L"Road",
		/*2*/L"POI",
		/*3*/L"VS",
		/*4*/L"Trafficcam",
		/*5*/L"WarnInfo",
		/*6*/L"SpeedLimit",
		/*7*/L"Obj",
		/*8*/L"Railway",
		/*9*/L"Vegetation",
		/*10*/L"Water",
		/*11*/L"Island",
		/*12*/L"BuildingLine",
		/*13*/L"BuildingArea",
		/*14*/L"Building",
		/*15*/L"Xian",
		/*16*/L"Diqu",
		/*17*/L"Province",
		/*18*/L"Country",
		/*19*/L"Mesh",
		/*20*/L"ErrorInfo",
		/*21*/L"QuestionInfo",
		/*22*/L"MarkInfo",
		/*23*/L"TestInfo",
		/*24*/L"Junction",
		/*25*/L"Compound",
		/*26*/L"Turn",
		/*27*/L"TimeLimit",
		/*28*/L"VehicleLimit",
		/*29*/L"Direction",
		/*30*/L"ExitInfo",
		/*31*/L"JunctionGuide",
		/*32*/L"JunctionReference",
		/*33*/L"JunctionSaFacility",
		/*34*/L"JunctionView",
		/*35*/L"Lane",
		/*36*/L"JunctionVideo",
		/*37*/L"JunctionVrview",
		/*38*/L"NewDirection",
		/*39*/L"NewLane",
		/*40*/L"NewTurn"
	};

	return layers[layid<_countof(layers) ? layid : 0] ;
}

inline unsigned GetLayerFixID(LPCWSTR szlayer)
{
    unsigned retval = 0;
    LPCWSTR  curlayer = nullptr;
    while( (curlayer=GetEnumLayer(++retval))!=nullptr )
    {
        if (lstrcmpiW(szlayer, curlayer)==0)
        {
            break;
        }
    }
    return curlayer!=nullptr ? retval : 0;
}

#endif