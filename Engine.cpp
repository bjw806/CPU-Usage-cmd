#include "Engine.h"
//#include "Graph.h"

void Engine::EachCPU() {
    Function Func;
    RAM Ram;
    CPU Cpu;
    //Graph Grap;
    HRESULT hres;//HRESULT 반환형 사용

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);   
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,            
        EOAC_NONE,
        NULL
    );
    
    IWbemLocator* pLoc = NULL; //하드웨어 정보를 읽기 위해 WMI 이용

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    IWbemServices* pSvc = NULL;

     hres = pLoc->ConnectServer( //WMI서버에 연결하기 위한 정보
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc
    );

    Func.position(0, 0);
    cout << "     WMI로 연결중..." << endl;

        hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );
    
    //IWbemServices 포인터로 WMI 요청

    IEnumWbemClassObject* pEnumerator = NULL;
    IWbemClassObject* pclsObj;

    //int uptime = 0;
    int i;
    int allcore = 1;
    while (1) {//무한반복
        i = 0;
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t("SELECT * FROM Win32_PerfFormattedData_PerfOS_Processor"),

            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pEnumerator);

        ULONG uReturn = 0;
        while (pEnumerator) {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
                &pclsObj, &uReturn);

            if (0 == uReturn) {
                break;
            }

            VARIANT vtProp;

            // Get the value of the Name property
            //hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
            hr = pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);

            if (allcore < i) {
                allcore = i;
            }
            char* pMultibyte = Func.Converter(vtProp.bstrVal);
            if (i < 10) {
                Func.position(5, i + 5);
                cout << "CORE " << i << ":  ";
                Cpu.progressbar(atoi(pMultibyte));
                Func.to_int(atoi(pMultibyte));
                cout << " %";
            }

            else if (i >= 10 && i < allcore) {
                Func.position(5, i + 5);
                cout << "CORE " << i << ": ";
                Cpu.progressbar(atoi(pMultibyte));
                Func.to_int(atoi(pMultibyte));
                cout << " %";
            }
            else if (i == allcore) {//12번 코어는 모든 쓰레드의 평균을 나타낸 것.
                Cpu.getallcore();//CPUUsage의 usage로 소수점까지 알아낸다.(그냥 CPU()를 하면 소수점이 나오지 않고 자료 반영속도도 느리다.)
                //Grap.caldigit(Cpu.returncoregraph(),uptime);
            }
            VariantClear(&vtProp);
            Ram.RAMusage();

            //IMPORTANT!!
            pclsObj->Release(); //함수를 호출 한 후 포인터를 null로 설정
            i++;
            //uptime++;
        }
    }

    //메모리 초기화
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    pclsObj->Release();
    CoUninitialize();
}