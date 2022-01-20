#include "Engine.h"
//#include "Graph.h"

void Engine::EachCPU() {
    Function Func;
    RAM Ram;
    CPU Cpu;
    //Graph Grap;
    HRESULT hres;//HRESULT ��ȯ�� ���

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
    
    IWbemLocator* pLoc = NULL; //�ϵ���� ������ �б� ���� WMI �̿�

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    IWbemServices* pSvc = NULL;

     hres = pLoc->ConnectServer( //WMI������ �����ϱ� ���� ����
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
    cout << "     WMI�� ������..." << endl;

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
    
    //IWbemServices �����ͷ� WMI ��û

    IEnumWbemClassObject* pEnumerator = NULL;
    IWbemClassObject* pclsObj;

    //int uptime = 0;
    int i;
    int allcore = 1;
    while (1) {//���ѹݺ�
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
            else if (i == allcore) {//12�� �ھ�� ��� �������� ����� ��Ÿ�� ��.
                Cpu.getallcore();//CPUUsage�� usage�� �Ҽ������� �˾Ƴ���.(�׳� CPU()�� �ϸ� �Ҽ����� ������ �ʰ� �ڷ� �ݿ��ӵ��� ������.)
                //Grap.caldigit(Cpu.returncoregraph(),uptime);
            }
            VariantClear(&vtProp);
            Ram.RAMusage();

            //IMPORTANT!!
            pclsObj->Release(); //�Լ��� ȣ�� �� �� �����͸� null�� ����
            i++;
            //uptime++;
        }
    }

    //�޸� �ʱ�ȭ
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    pclsObj->Release();
    CoUninitialize();
}