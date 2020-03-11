#include <mrc_base.h>
 int16 SCRW;  
 int16 SCRH;

void mpc_init(void){
	mr_screeninfo screen;
    
    //提取MRP中的“短名称”字段，创建以MRP短名称命名的目录
	/*
    mrc_GetMrpInfo((char*)mrc_getPackName(), MRP_FILENAME, (uint8*)STOREDIR, DIRLEN);

    if(MR_IS_DIR != mrc_fileState(STOREDIR))
    {
        mrc_mkDir(STOREDIR);
    }
    mrc_strcat(STOREDIR, "/");

//     StackInit();
    //enable_smallfont=(char)readCfg(CFG_SMALLFONT);
    func_state=0;
	*/
    mrc_getScreenInfo(&screen);
    SCRW = (int16)screen.width;
    SCRH = (int16)screen.height;
	
}