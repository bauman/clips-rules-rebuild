# These must be set before the OBJECT libraries below are defined so the flags/defines
# apply to their compilation. WIN_MVC selects the MSVC code paths in the CLIPS source.
if(WIN32)
	add_definitions(-DWIN_MVC=1)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	set(CMAKE_C_OUTPUT_EXTENSION .o)
	add_compile_options("-fpic")
endif()
set( OBJNAMES
        agenda analysis argacces bload bmathfun bsave
        classcom classexm classfun classinf classini
        classpsr clsltpsr commline conscomp constrct
        constrnt crstrtgy cstrcbin cstrccom cstrcpsr
        cstrnbin cstrnchk cstrncmp cstrnops cstrnpsr
        cstrnutl default defins developr dffctbin dffctbsc
        dffctcmp dffctdef dffctpsr dffnxbin dffnxcmp dffnxexe
        dffnxfun dffnxpsr dfinsbin dfinscmp drive emathfun
        engine envrnmnt envrnbld evaluatn expressn exprnbin
        exprnops exprnpsr extnfunc factbin factbld factcmp
        factcom factfun factgen facthsh factfile factlhs factmch
        factmngr factprt factqpsr factqury factrete factrhs
        filecom filertr fileutil generate genrcbin genrccmp
        genrccom genrcexe genrcfun genrcpsr globlbin globlbsc
        globlcmp globlcom globldef globlpsr immthpsr incrrset
        inherpsr inscom insfile insfun insmngr insmoddp
        insmult inspsr insquery insqypsr iofun lgcldpnd
        memalloc miscfun modulbin modulbsc modulcmp moduldef
        modulpsr modulutl msgcom msgfun msgpass msgpsr
        multifld multifun objbin objcmp objrtbin objrtbld
        objrtcmp objrtfnx objrtgen objrtmch parsefun pattern
        pprint prccode prcdrfun prcdrpsr prdctfun prntutil
        proflfun reorder reteutil retract router rulebin
        rulebld rulebsc rulecmp rulecom rulecstr ruledef
        ruledlt rulelhs rulepsr scanner sortfun strngfun
        strngrtr symblbin symblcmp symbol sysdep textpro
        tmpltbin tmpltbsc tmpltcmp tmpltdef tmpltfun tmpltlhs
        tmpltpsr tmpltrhs tmpltutl userdata userfunctions
        utility watch
)

add_library(agenda OBJECT agenda.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h engine.h lgcldpnd.h retract.h
        memalloc.h modulutl.h scanner.h prntutil.h reteutil.h rulecom.h
        router.h rulebsc.h strngrtr.h sysdep.h watch.h)

add_library(analysis OBJECT analysis.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h cstrnchk.h constrnt.h evaluatn.h cstrnutl.h cstrnops.h
        exprnpsr.h extnfunc.h expressn.h exprnops.h constrct.h userdata.h
        moduldef.h utility.h insfun.h object.h multifld.h symbol.h match.h
        network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h
        cstrccom.h objrtmch.h scanner.h generate.h analysis.h reorder.h
        pattern.h memalloc.h modulutl.h prntutil.h router.h rulecstr.h
        rulepsr.h watch.h)

add_library(argacces OBJECT argacces.c setup.h envrnmnt.h entities.h usrsetup.h
        cstrnchk.h constrnt.h evaluatn.h constant.h extnfunc.h expressn.h
        exprnops.h constrct.h userdata.h moduldef.h utility.h insfun.h
        object.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h factmngr.h
        tmpltdef.h factbld.h facthsh.h inscom.h prntutil.h router.h sysdep.h
        argacces.h)

add_library(bload OBJECT bload.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h bsave.h cstrnbin.h exprnpsr.h
        scanner.h memalloc.h prntutil.h router.h bload.h exprnbin.h sysdep.h
        symblbin.h)

add_library(bmathfun OBJECT bmathfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnpsr.h
        scanner.h prntutil.h router.h bmathfun.h)

add_library(bsave OBJECT bsave.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h bload.h exprnbin.h sysdep.h
        symblbin.h cstrnbin.h exprnpsr.h scanner.h memalloc.h prntutil.h
        router.h bsave.h)

add_library(classcom OBJECT classcom.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h argacces.h classfun.h scanner.h classcom.h classini.h
        modulutl.h msgcom.h msgpass.h prntutil.h router.h)

add_library(classexm OBJECT classexm.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h classcom.h
        classfun.h scanner.h classini.h memalloc.h msgcom.h msgpass.h msgfun.h
        prntutil.h router.h strngrtr.h sysdep.h classexm.h)

add_library(classfun OBJECT classfun.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h classcom.h classini.h cstrcpsr.h strngfun.h inscom.h
        insmngr.h memalloc.h modulutl.h scanner.h msgfun.h msgpass.h
        prntutil.h router.h classfun.h)

add_library(classinf OBJECT classinf.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h classcom.h
        classexm.h classfun.h scanner.h classini.h memalloc.h msgcom.h
        msgpass.h msgfun.h prntutil.h classinf.h)

add_library(classini OBJECT classini.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classexm.h
        classfun.h scanner.h classinf.h classpsr.h cstrcpsr.h strngfun.h
        inscom.h memalloc.h modulpsr.h modulutl.h msgcom.h msgpass.h watch.h
        defins.h insquery.h bload.h exprnbin.h sysdep.h symblbin.h objbin.h
        objcmp.h objrtbld.h objrtfnx.h classini.h)

add_library(classpsr OBJECT classpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h classcom.h classfun.h scanner.h clsltpsr.h cstrcpsr.h
        strngfun.h inherpsr.h memalloc.h modulpsr.h modulutl.h msgpsr.h
        pprint.h prntutil.h router.h classpsr.h)

add_library(clsltpsr OBJECT clsltpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h
        scanner.h cstrnchk.h cstrnpsr.h cstrnutl.h default.h memalloc.h
        pprint.h prntutil.h router.h clsltpsr.h)

add_library(commline OBJECT commline.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h argacces.h expressn.h exprnops.h constrct.h userdata.h
        moduldef.h utility.h evaluatn.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrcpsr.h
        strngfun.h exprnpsr.h scanner.h fileutil.h memalloc.h pprint.h
        prcdrfun.h prcdrpsr.h prntutil.h router.h strngrtr.h sysdep.h
        commline.h)

add_library(conscomp OBJECT conscomp.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrncmp.h
        exprnpsr.h scanner.h memalloc.h modulcmp.h prntutil.h router.h
        sysdep.h dffnxcmp.h dffnxfun.h tmpltcmp.h tmpltdef.h factbld.h
        globlcmp.h globldef.h genrccmp.h genrcfun.h objcmp.h)

add_library(constrct OBJECT constrct.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h commline.h
        cstrcpsr.h strngfun.h exprnpsr.h scanner.h memalloc.h miscfun.h
        modulutl.h prcdrfun.h prcdrpsr.h prntutil.h router.h sysdep.h watch.h)

add_library(constrnt OBJECT constrnt.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h memalloc.h
        router.h scanner.h)

add_library(crstrtgy OBJECT crstrtgy.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h argacces.h memalloc.h pattern.h
        scanner.h reorder.h reteutil.h rulecom.h)

add_library(cstrcbin OBJECT cstrcbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h cstrcbin.h)

add_library(cstrccom OBJECT cstrccom.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h extnfunc.h evaluatn.h expressn.h exprnops.h constrct.h
        userdata.h moduldef.h utility.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h symblcmp.h cstrccom.h objrtmch.h memalloc.h argacces.h
        modulutl.h scanner.h prntutil.h router.h commline.h sysdep.h bload.h
        exprnbin.h symblbin.h cstrcpsr.h strngfun.h)

add_library(cstrcpsr OBJECT cstrcpsr.c setup.h envrnmnt.h entities.h usrsetup.h router.h
        watch.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h prcdrpsr.h
        exprnpsr.h scanner.h memalloc.h modulutl.h modulpsr.h pprint.h
        prntutil.h strngrtr.h sysdep.h cstrcpsr.h strngfun.h)

add_library(cstrnbin OBJECT cstrnbin.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h memalloc.h prntutil.h router.h bload.h utility.h evaluatn.h
        moduldef.h userdata.h insfun.h object.h constrct.h constrnt.h
        expressn.h exprnops.h multifld.h symbol.h match.h network.h ruledef.h
        agenda.h crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h
        objrtmch.h exprnbin.h sysdep.h symblbin.h bsave.h cstrnbin.h)

add_library(cstrnchk OBJECT cstrnchk.c setup.h envrnmnt.h entities.h usrsetup.h
        cstrnutl.h constrnt.h evaluatn.h constant.h extnfunc.h expressn.h
        exprnops.h constrct.h userdata.h moduldef.h utility.h insfun.h
        object.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h prntutil.h
        router.h classcom.h classexm.h inscom.h cstrnchk.h)

add_library(cstrncmp OBJECT cstrncmp.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h conscomp.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h memalloc.h prntutil.h
        router.h sysdep.h cstrncmp.h)

add_library(cstrnops OBJECT cstrnops.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h constrnt.h evaluatn.h cstrnchk.h cstrnutl.h extnfunc.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        insfun.h object.h multifld.h symbol.h match.h network.h ruledef.h
        agenda.h crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h
        memalloc.h router.h scanner.h cstrnops.h)

add_library(cstrnpsr OBJECT cstrnpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h cstrnchk.h constrnt.h evaluatn.h cstrnutl.h expressn.h
        exprnops.h constrct.h userdata.h moduldef.h utility.h insfun.h
        object.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h
        memalloc.h pprint.h prntutil.h router.h scanner.h sysdep.h cstrnpsr.h)

add_library(cstrnutl OBJECT cstrnutl.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h memalloc.h
        router.h scanner.h cstrnutl.h)

add_library(default OBJECT default.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        constrnt.h evaluatn.h cstrnchk.h cstrnutl.h exprnpsr.h extnfunc.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        insfun.h object.h multifld.h symbol.h match.h network.h ruledef.h
        agenda.h crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h
        scanner.h factmngr.h tmpltdef.h factbld.h facthsh.h inscom.h pprint.h
        prntutil.h router.h default.h)

add_library(defins OBJECT defins.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h dfinsbin.h defins.h dfinscmp.h argacces.h classcom.h
        classfun.h scanner.h cstrcpsr.h strngfun.h inspsr.h memalloc.h
        modulpsr.h modulutl.h pprint.h prntutil.h router.h)

add_library(developr OBJECT developr.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h factmngr.h
        tmpltdef.h factbld.h facthsh.h inscom.h modulutl.h scanner.h
        prntutil.h router.h classcom.h classfun.h developr.h)

add_library(dffctbin OBJECT dffctbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h dffctdef.h memalloc.h dffctbin.h cstrcbin.h
        modulbin.h)

add_library(dffctbsc OBJECT dffctbsc.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrcpsr.h
        strngfun.h dffctdef.h dffctpsr.h factrhs.h factmngr.h tmpltdef.h
        factbld.h facthsh.h scanner.h memalloc.h router.h dffctbin.h
        cstrcbin.h modulbin.h dffctcmp.h dffctbsc.h)

add_library(dffctcmp OBJECT dffctcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h dffctdef.h dffctcmp.h)

add_library(dffctdef OBJECT dffctdef.c setup.h envrnmnt.h entities.h usrsetup.h
        dffctbsc.h dffctdef.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h
        dffctpsr.h memalloc.h bload.h exprnbin.h sysdep.h symblbin.h
        dffctbin.h cstrcbin.h modulbin.h dffctcmp.h)

add_library(dffctpsr OBJECT dffctpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h cstrcpsr.h strngfun.h dffctbsc.h dffctdef.h factrhs.h
        factmngr.h tmpltdef.h factbld.h facthsh.h scanner.h memalloc.h
        modulutl.h pprint.h prntutil.h router.h dffctpsr.h)

add_library(dffnxbin OBJECT dffnxbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h cstrcbin.h memalloc.h modulbin.h dffnxbin.h
        dffnxfun.h)

add_library(dffnxcmp OBJECT dffnxcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h dffnxcmp.h dffnxfun.h)

add_library(dffnxexe OBJECT dffnxexe.c setup.h envrnmnt.h entities.h usrsetup.h
        constrct.h userdata.h moduldef.h utility.h evaluatn.h constant.h
        insfun.h object.h constrnt.h expressn.h exprnops.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h prcdrfun.h prccode.h scanner.h
        prntutil.h proflfun.h router.h watch.h dffnxexe.h dffnxfun.h)

add_library(dffnxfun OBJECT dffnxfun.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h dffnxbin.h dffnxfun.h dffnxcmp.h cstrcpsr.h strngfun.h
        dffnxpsr.h modulpsr.h scanner.h dffnxexe.h watch.h argacces.h
        memalloc.h modulutl.h prntutil.h router.h)

add_library(dffnxpsr OBJECT dffnxpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h genrccom.h genrcfun.h cstrcpsr.h strngfun.h dffnxfun.h
        exprnpsr.h scanner.h memalloc.h modulutl.h pprint.h prccode.h
        prntutil.h router.h dffnxpsr.h)

add_library(dfinsbin OBJECT dfinsbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h cstrcbin.h defins.h memalloc.h modulbin.h
        dfinsbin.h)

add_library(dfinscmp OBJECT dfinscmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h defins.h dfinscmp.h)

add_library(drive OBJECT drive.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h engine.h lgcldpnd.h retract.h
        incrrset.h memalloc.h prntutil.h reteutil.h rulecom.h router.h drive.h)

add_library(emathfun OBJECT emathfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h miscfun.h
        prntutil.h router.h emathfun.h)

add_library(engine OBJECT engine.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h argacces.h commline.h factmngr.h
        tmpltdef.h factbld.h facthsh.h inscom.h memalloc.h modulutl.h
        scanner.h prccode.h prcdrfun.h prntutil.h proflfun.h reteutil.h
        rulecom.h retract.h router.h ruledlt.h sysdep.h watch.h engine.h
        lgcldpnd.h)

add_library(envrnbld OBJECT envrnbld.c setup.h envrnmnt.h entities.h usrsetup.h
        bmathfun.h evaluatn.h constant.h commline.h emathfun.h engine.h
        lgcldpnd.h match.h network.h ruledef.h constrct.h userdata.h
        moduldef.h utility.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h objrtmch.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h retract.h filecom.h
        iofun.h memalloc.h miscfun.h multifun.h parsefun.h pprint.h prccode.h
        scanner.h prcdrfun.h prdctfun.h prntutil.h proflfun.h router.h
        sortfun.h strngfun.h sysdep.h textpro.h watch.h dffctdef.h genrccom.h
        genrcfun.h dffnxfun.h globldef.h tmpltdef.h factbld.h classini.h
        envrnbld.h)

add_library(envrnmnt OBJECT envrnmnt.c setup.h envrnmnt.h entities.h usrsetup.h
        bmathfun.h evaluatn.h constant.h commline.h emathfun.h engine.h
        lgcldpnd.h match.h network.h ruledef.h constrct.h userdata.h
        moduldef.h utility.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h objrtmch.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h retract.h filecom.h
        iofun.h memalloc.h miscfun.h multifun.h parsefun.h prccode.h scanner.h
        prcdrfun.h prdctfun.h prntutil.h proflfun.h router.h sortfun.h
        strngfun.h sysdep.h textpro.h watch.h dffctdef.h genrccom.h genrcfun.h
        dffnxfun.h globldef.h tmpltdef.h factbld.h classini.h)

add_library(evaluatn OBJECT evaluatn.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h commline.h
        factmngr.h tmpltdef.h factbld.h facthsh.h memalloc.h modulutl.h
        scanner.h router.h prcdrfun.h prntutil.h exprnpsr.h proflfun.h
        sysdep.h dffnxfun.h genrccom.h genrcfun.h inscom.h)

add_library(expressn OBJECT expressn.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h memalloc.h prntutil.h router.h)

add_library(exprnbin OBJECT exprnbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h dffctdef.h memalloc.h genrcbin.h genrcfun.h
        dffnxbin.h dffnxfun.h factmngr.h tmpltdef.h factbld.h facthsh.h
        tmpltbin.h cstrcbin.h modulbin.h globlbin.h globldef.h objbin.h
        inscom.h)

add_library(exprnops OBJECT exprnops.c setup.h envrnmnt.h entities.h usrsetup.h
        cstrnchk.h constrnt.h evaluatn.h constant.h cstrnops.h cstrnutl.h
        extnfunc.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h insfun.h object.h multifld.h symbol.h match.h network.h
        ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h cstrccom.h
        objrtmch.h memalloc.h prntutil.h router.h)

add_library(exprnpsr OBJECT exprnpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrnchk.h
        memalloc.h modulutl.h scanner.h pprint.h prcdrfun.h prntutil.h
        router.h strngrtr.h genrccom.h genrcfun.h dffnxfun.h exprnpsr.h)

add_library(extnfunc OBJECT extnfunc.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnpsr.h
        scanner.h factmngr.h tmpltdef.h factbld.h facthsh.h memalloc.h
        router.h inscom.h)

add_library(factbin OBJECT factbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h factmngr.h tmpltdef.h factbld.h facthsh.h
        memalloc.h pattern.h scanner.h reorder.h reteutil.h rulecom.h
        rulebin.h cstrcbin.h modulbin.h factbin.h)

add_library(factbld OBJECT factbld.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h factcmp.h pattern.h scanner.h
        reorder.h factgen.h factlhs.h factmch.h factbld.h factmngr.h
        tmpltdef.h facthsh.h memalloc.h modulutl.h reteutil.h rulecom.h
        router.h)

add_library(factcmp OBJECT factcmp.c setup.h envrnmnt.h entities.h usrsetup.h factbld.h
        network.h match.h ruledef.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h objrtmch.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h factmngr.h tmpltdef.h
        facthsh.h factcmp.h pattern.h scanner.h reorder.h)

add_library(factcom OBJECT factcom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h factmngr.h tmpltdef.h factbld.h
        facthsh.h factrhs.h scanner.h pprint.h prntutil.h router.h sysdep.h
        tmpltutl.h factcom.h)

add_library(factfile OBJECT factfile.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h bload.h
        exprnbin.h sysdep.h symblbin.h cstrcpsr.h strngfun.h factmngr.h
        tmpltdef.h factbld.h facthsh.h factrhs.h scanner.h insmngr.h inscom.h
        memalloc.h modulpsr.h modulutl.h prntutil.h router.h strngrtr.h
        tmpltutl.h factfile.h)

add_library(factfun OBJECT factfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h prntutil.h router.h sysdep.h
        tmpltutl.h factmngr.h tmpltdef.h factbld.h facthsh.h factfun.h)

add_library(factgen OBJECT factgen.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        constrct.h userdata.h moduldef.h utility.h evaluatn.h insfun.h
        object.h constrnt.h expressn.h exprnops.h multifld.h symbol.h match.h
        network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h exprnpsr.h scanner.h factmch.h
        factbld.h factmngr.h tmpltdef.h facthsh.h factprt.h factrete.h
        memalloc.h pattern.h reorder.h prcdrpsr.h reteutil.h rulecom.h
        router.h sysdep.h tmpltfun.h tmpltlhs.h tmpltutl.h factgen.h)

add_library(facthsh OBJECT facthsh.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        factmngr.h conscomp.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h tmpltdef.h factbld.h
        facthsh.h memalloc.h router.h sysdep.h lgcldpnd.h)

add_library(factlhs OBJECT factlhs.c setup.h envrnmnt.h entities.h usrsetup.h cstrcpsr.h
        strngfun.h modulpsr.h evaluatn.h constant.h moduldef.h userdata.h
        symbol.h scanner.h modulutl.h pattern.h expressn.h exprnops.h
        constrct.h utility.h insfun.h object.h constrnt.h multifld.h match.h
        network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h reorder.h pprint.h prntutil.h
        router.h tmpltdef.h factbld.h tmpltlhs.h tmpltpsr.h tmpltutl.h
        factmngr.h facthsh.h factlhs.h)

add_library(factmch OBJECT factmch.c setup.h envrnmnt.h entities.h usrsetup.h drive.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h engine.h lgcldpnd.h retract.h
        factgen.h reorder.h pattern.h scanner.h factrete.h incrrset.h
        memalloc.h prntutil.h reteutil.h rulecom.h router.h sysdep.h
        tmpltdef.h factbld.h factmch.h factmngr.h facthsh.h)

add_library(factmngr OBJECT factmngr.c setup.h envrnmnt.h entities.h usrsetup.h
        commline.h default.h constrnt.h evaluatn.h constant.h engine.h
        lgcldpnd.h match.h network.h ruledef.h constrct.h userdata.h
        moduldef.h utility.h insfun.h object.h expressn.h exprnops.h
        multifld.h symbol.h objrtmch.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h retract.h factbin.h factbld.h
        factcmp.h pattern.h scanner.h reorder.h factcom.h factfile.h factfun.h
        factmngr.h tmpltdef.h facthsh.h factmch.h factqury.h factrhs.h
        memalloc.h prntutil.h router.h strngrtr.h sysdep.h tmpltbsc.h
        tmpltfun.h tmpltutl.h watch.h cstrnchk.h)

add_library(factprt OBJECT factprt.c setup.h envrnmnt.h entities.h usrsetup.h factgen.h
        reorder.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h pattern.h
        scanner.h prntutil.h router.h factprt.h)

add_library(factqpsr OBJECT factqpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        exprnpsr.h extnfunc.h evaluatn.h constant.h expressn.h exprnops.h
        constrct.h userdata.h moduldef.h utility.h insfun.h object.h
        constrnt.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h scanner.h
        factqury.h factmngr.h tmpltdef.h factbld.h facthsh.h modulutl.h
        prcdrpsr.h pprint.h prntutil.h router.h strngrtr.h factqpsr.h)

add_library(factqury OBJECT factqury.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h memalloc.h
        exprnpsr.h scanner.h modulutl.h tmpltutl.h factmngr.h tmpltdef.h
        factbld.h facthsh.h factqpsr.h prcdrfun.h prntutil.h router.h
        factqury.h)

add_library(factrete OBJECT factrete.c setup.h envrnmnt.h entities.h usrsetup.h drive.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h engine.h lgcldpnd.h retract.h
        factgen.h reorder.h pattern.h scanner.h factmch.h factbld.h factmngr.h
        tmpltdef.h facthsh.h incrrset.h memalloc.h reteutil.h rulecom.h
        router.h factrete.h)

add_library(factrhs OBJECT factrhs.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h cstrcpsr.h strngfun.h exprnpsr.h scanner.h modulutl.h
        modulpsr.h pattern.h reorder.h pprint.h prntutil.h router.h strngrtr.h
        tmpltpsr.h tmpltdef.h factbld.h tmpltrhs.h tmpltutl.h factmngr.h
        facthsh.h factrhs.h)

add_library(filecom OBJECT filecom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h bload.h exprnbin.h sysdep.h
        symblbin.h bsave.h commline.h cstrcpsr.h strngfun.h fileutil.h
        memalloc.h router.h filecom.h)

add_library(filertr OBJECT filertr.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        memalloc.h router.h sysdep.h filertr.h)

add_library(fileutil OBJECT fileutil.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h commline.h
        cstrcpsr.h strngfun.h memalloc.h prcdrfun.h pprint.h prntutil.h
        router.h scanner.h strngrtr.h sysdep.h filecom.h fileutil.h)

add_library(generate OBJECT generate.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnpsr.h
        scanner.h globlpsr.h memalloc.h pattern.h reorder.h prntutil.h
        router.h generate.h analysis.h)

add_library(genrcbin OBJECT genrcbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h cstrcbin.h genrccom.h genrcfun.h memalloc.h
        modulbin.h objbin.h router.h genrcbin.h)

add_library(genrccmp OBJECT genrccmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h genrccom.h genrcfun.h
        objcmp.h genrccmp.h)

add_library(genrccom OBJECT genrccom.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h bload.h
        exprnbin.h sysdep.h symblbin.h classcom.h inscom.h cstrcpsr.h
        strngfun.h genrcbin.h genrcfun.h genrccmp.h genrcexe.h genrcpsr.h
        memalloc.h modulpsr.h scanner.h modulutl.h router.h strngrtr.h watch.h
        prntutil.h genrccom.h)

add_library(genrcexe OBJECT genrcexe.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h
        scanner.h argacces.h genrccom.h genrcfun.h prcdrfun.h prccode.h
        prntutil.h proflfun.h router.h genrcexe.h)

add_library(genrcfun OBJECT genrcfun.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h classcom.h classfun.h scanner.h argacces.h cstrcpsr.h
        strngfun.h genrccom.h genrcfun.h genrcexe.h memalloc.h modulutl.h
        prccode.h prntutil.h router.h)

add_library(genrcpsr OBJECT genrcpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h dffnxfun.h classfun.h scanner.h classcom.h cstrcpsr.h
        strngfun.h exprnpsr.h genrccom.h genrcfun.h immthpsr.h memalloc.h
        modulutl.h pprint.h prcdrpsr.h prccode.h prntutil.h router.h
        genrcpsr.h)

add_library(globlbin OBJECT globlbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h globlbsc.h globldef.h memalloc.h globlbin.h
        modulbin.h cstrcbin.h)

add_library(globlbsc OBJECT globlbsc.c setup.h envrnmnt.h entities.h usrsetup.h
        constrct.h userdata.h moduldef.h utility.h evaluatn.h constant.h
        insfun.h object.h constrnt.h expressn.h exprnops.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h globlbin.h modulbin.h cstrcbin.h
        globldef.h globlcmp.h globlcom.h watch.h globlbsc.h)

add_library(globlcmp OBJECT globlcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h globldef.h globlcmp.h)

add_library(globlcom OBJECT globlcom.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h globldef.h
        prntutil.h router.h globlcom.h)

add_library(globldef OBJECT globldef.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h globlbin.h modulbin.h cstrcbin.h globldef.h commline.h
        globlbsc.h globlcmp.h globlcom.h globlpsr.h memalloc.h modulpsr.h
        scanner.h modulutl.h prntutil.h router.h strngrtr.h)

add_library(globlpsr OBJECT globlpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h cstrcpsr.h strngfun.h exprnpsr.h scanner.h globlbsc.h
        globldef.h memalloc.h modulpsr.h modulutl.h pprint.h prntutil.h
        router.h watch.h globlpsr.h)

add_library(immthpsr OBJECT immthpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h
        scanner.h cstrnutl.h exprnpsr.h genrcpsr.h genrcfun.h memalloc.h
        prccode.h immthpsr.h)

add_library(incrrset OBJECT incrrset.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h argacces.h drive.h engine.h
        lgcldpnd.h retract.h pattern.h scanner.h reorder.h router.h reteutil.h
        rulecom.h incrrset.h)

add_library(inherpsr OBJECT inherpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h
        scanner.h memalloc.h modulutl.h pprint.h prntutil.h router.h
        inherpsr.h)

add_library(inscom OBJECT inscom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h classcom.h classfun.h scanner.h
        classinf.h commline.h exprnpsr.h insfile.h insmngr.h inscom.h
        insmoddp.h insmult.h inspsr.h lgcldpnd.h memalloc.h msgcom.h msgpass.h
        msgfun.h prntutil.h router.h strngrtr.h sysdep.h)

add_library(insfile OBJECT insfile.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h classcom.h classfun.h scanner.h
        memalloc.h factmngr.h tmpltdef.h factbld.h facthsh.h inscom.h
        insmngr.h inspsr.h prntutil.h router.h strngrtr.h symblbin.h sysdep.h
        insfile.h)

add_library(insfun OBJECT insfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h classcom.h classfun.h scanner.h
        cstrnchk.h drive.h engine.h lgcldpnd.h retract.h inscom.h insmngr.h
        memalloc.h modulutl.h msgcom.h msgpass.h msgfun.h prccode.h prntutil.h
        router.h)

add_library(insmngr OBJECT insmngr.c setup.h envrnmnt.h entities.h usrsetup.h network.h
        match.h ruledef.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h objrtmch.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h drive.h lgcldpnd.h
        objrtfnx.h classcom.h classfun.h scanner.h cstrnchk.h engine.h
        retract.h memalloc.h miscfun.h modulutl.h msgcom.h msgpass.h msgfun.h
        prccode.h prntutil.h router.h sysdep.h insmngr.h inscom.h watch.h)

add_library(insmoddp OBJECT insmoddp.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h inscom.h
        insmngr.h inspsr.h memalloc.h miscfun.h msgcom.h msgpass.h msgfun.h
        prccode.h scanner.h prntutil.h router.h insmoddp.h)

add_library(insmult OBJECT insmult.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h msgfun.h msgpass.h multifun.h
        prntutil.h router.h insmult.h)

add_library(inspsr OBJECT inspsr.c setup.h envrnmnt.h entities.h usrsetup.h classcom.h
        cstrccom.h moduldef.h userdata.h constrct.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h
        classinf.h exprnpsr.h pprint.h prntutil.h router.h inspsr.h)

add_library(insquery OBJECT insquery.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h classcom.h
        classfun.h scanner.h exprnpsr.h insmngr.h inscom.h insqypsr.h
        memalloc.h prcdrfun.h prntutil.h router.h insquery.h)

add_library(insqypsr OBJECT insqypsr.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h exprnpsr.h
        scanner.h insquery.h prcdrpsr.h pprint.h prntutil.h router.h
        strngrtr.h insqypsr.h)

add_library(iofun OBJECT iofun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h commline.h exprnpsr.h scanner.h
        filertr.h memalloc.h miscfun.h pprint.h prcdrfun.h prntutil.h router.h
        strngrtr.h sysdep.h iofun.h)

add_library(lgcldpnd OBJECT lgcldpnd.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h engine.h
        lgcldpnd.h retract.h factmngr.h tmpltdef.h factbld.h facthsh.h
        memalloc.h pattern.h scanner.h reorder.h reteutil.h rulecom.h router.h)

add_library(main OBJECT main.c clips.h setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h memalloc.h
        cstrcpsr.h strngfun.h fileutil.h envrnbld.h commline.h prntutil.h
        router.h filertr.h strngrtr.h iofun.h sysdep.h bmathfun.h exprnpsr.h
        scanner.h miscfun.h watch.h modulbsc.h bload.h exprnbin.h symblbin.h
        bsave.h rulebsc.h engine.h lgcldpnd.h retract.h drive.h incrrset.h
        rulecom.h dffctdef.h dffctbsc.h tmpltdef.h factbld.h tmpltbsc.h
        tmpltfun.h factmngr.h facthsh.h factcom.h factfile.h factfun.h
        globldef.h globlbsc.h globlcom.h dffnxfun.h genrccom.h genrcfun.h
        classcom.h classexm.h classfun.h classinf.h classini.h classpsr.h
        defins.h inscom.h insfile.h insmngr.h msgcom.h msgpass.h)

add_library(memalloc OBJECT memalloc.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h memalloc.h prntutil.h router.h utility.h evaluatn.h
        moduldef.h userdata.h insfun.h object.h constrct.h constrnt.h
        expressn.h exprnops.h multifld.h symbol.h match.h network.h ruledef.h
        agenda.h crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h
        objrtmch.h)

add_library(miscfun OBJECT miscfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h exprnpsr.h scanner.h memalloc.h
        prntutil.h router.h sysdep.h dffnxfun.h factfun.h factmngr.h
        tmpltdef.h factbld.h facthsh.h tmpltutl.h miscfun.h)

add_library(modulbin OBJECT modulbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h cstrcbin.h memalloc.h modulbin.h)

add_library(modulbsc OBJECT modulbsc.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h bload.h
        exprnbin.h sysdep.h symblbin.h modulbin.h cstrcbin.h modulcmp.h
        prntutil.h router.h modulbsc.h)

add_library(modulcmp OBJECT modulcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h sysdep.h modulcmp.h)

add_library(moduldef OBJECT moduldef.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h bload.h
        exprnbin.h sysdep.h symblbin.h modulbin.h cstrcbin.h memalloc.h
        modulbsc.h modulcmp.h modulpsr.h scanner.h prntutil.h router.h)

add_library(modulpsr OBJECT modulpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrcpsr.h
        strngfun.h memalloc.h modulutl.h scanner.h pprint.h prntutil.h
        router.h bload.h exprnbin.h sysdep.h symblbin.h modulpsr.h)

add_library(modulutl OBJECT modulutl.c setup.h envrnmnt.h entities.h usrsetup.h
        cstrcpsr.h strngfun.h memalloc.h modulpsr.h evaluatn.h constant.h
        moduldef.h userdata.h symbol.h scanner.h pprint.h prntutil.h router.h
        sysdep.h watch.h expressn.h exprnops.h constrct.h utility.h insfun.h
        object.h constrnt.h multifld.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h
        modulutl.h)

add_library(msgcom OBJECT msgcom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h bload.h exprnbin.h sysdep.h
        symblbin.h classcom.h classfun.h scanner.h classinf.h msgpsr.h
        insmoddp.h msgfun.h msgpass.h memalloc.h prccode.h prntutil.h router.h
        watch.h msgcom.h)

add_library(msgfun OBJECT msgfun.c setup.h envrnmnt.h entities.h usrsetup.h classcom.h
        cstrccom.h moduldef.h userdata.h constrct.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h
        inscom.h memalloc.h msgcom.h msgpass.h prccode.h prntutil.h router.h
        msgfun.h)

add_library(msgpass OBJECT msgpass.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h classcom.h classfun.h scanner.h
        commline.h exprnpsr.h inscom.h memalloc.h msgcom.h msgpass.h msgfun.h
        prccode.h prcdrfun.h prntutil.h proflfun.h router.h strngfun.h)

add_library(msgpsr OBJECT msgpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h classcom.h classfun.h scanner.h cstrcpsr.h strngfun.h
        cstrnchk.h exprnpsr.h memalloc.h modulutl.h msgcom.h msgpass.h
        msgfun.h pprint.h prccode.h prntutil.h router.h strngrtr.h msgpsr.h)

add_library(multifld OBJECT multifld.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h evaluatn.h exprnops.h expressn.h constrct.h userdata.h
        moduldef.h utility.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h memalloc.h scanner.h prntutil.h
        router.h strngrtr.h)

add_library(multifun OBJECT multifun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnpsr.h
        scanner.h memalloc.h multifun.h pprint.h prcdrpsr.h prcdrfun.h
        prntutil.h router.h)

add_library(objbin OBJECT objbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h classcom.h classfun.h scanner.h classini.h
        cstrcbin.h cstrnbin.h memalloc.h modulbin.h msgcom.h msgpass.h
        msgfun.h prntutil.h router.h objrtbin.h objbin.h)

add_library(objcmp OBJECT objcmp.c setup.h envrnmnt.h entities.h usrsetup.h conscomp.h
        constrct.h userdata.h moduldef.h utility.h evaluatn.h constant.h
        insfun.h object.h constrnt.h expressn.h exprnops.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h cstrccom.h objrtmch.h
        extnfunc.h symblcmp.h classcom.h classfun.h scanner.h classini.h
        cstrncmp.h objrtfnx.h sysdep.h objrtcmp.h objcmp.h)

add_library(objrtbin OBJECT objrtbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h classfun.h scanner.h classcom.h memalloc.h
        pattern.h reorder.h reteutil.h rulecom.h rulebin.h cstrcbin.h
        modulbin.h objrtbin.h)

add_library(objrtbld OBJECT objrtbld.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h
        scanner.h cstrnutl.h cstrnchk.h cstrnops.h drive.h inscom.h insmngr.h
        memalloc.h pattern.h reorder.h prntutil.h reteutil.h rulecom.h
        rulepsr.h exprnpsr.h objrtgen.h objrtfnx.h pprint.h router.h
        objrtbin.h objrtcmp.h objrtbld.h)

add_library(objrtcmp OBJECT objrtcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h classcom.h objrtfnx.h
        pattern.h scanner.h reorder.h sysdep.h objrtcmp.h)

add_library(objrtfnx OBJECT objrtfnx.c setup.h envrnmnt.h entities.h usrsetup.h
        classcom.h cstrccom.h moduldef.h userdata.h constrct.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h
        scanner.h bload.h exprnbin.h sysdep.h symblbin.h drive.h engine.h
        lgcldpnd.h retract.h memalloc.h prntutil.h reteutil.h rulecom.h
        router.h objrtfnx.h)

add_library(objrtgen OBJECT objrtgen.c setup.h envrnmnt.h entities.h usrsetup.h
        classfun.h object.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h scanner.h
        classcom.h objrtfnx.h objrtgen.h reorder.h pattern.h)

add_library(objrtmch OBJECT objrtmch.c setup.h envrnmnt.h entities.h usrsetup.h
        classfun.h object.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h scanner.h
        classcom.h memalloc.h drive.h engine.h lgcldpnd.h retract.h incrrset.h
        objrtfnx.h prntutil.h reteutil.h rulecom.h ruledlt.h reorder.h
        pattern.h router.h insmngr.h inscom.h)

add_library(parsefun OBJECT parsefun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrcpsr.h
        strngfun.h exprnpsr.h scanner.h memalloc.h pprint.h prcdrpsr.h
        prntutil.h router.h strngrtr.h parsefun.h)

add_library(pattern OBJECT pattern.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        constrnt.h evaluatn.h cstrnchk.h cstrnutl.h exprnpsr.h extnfunc.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        insfun.h object.h multifld.h symbol.h match.h network.h ruledef.h
        agenda.h crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h
        scanner.h memalloc.h pprint.h prntutil.h reteutil.h rulecom.h router.h
        rulecmp.h pattern.h reorder.h)

add_library(pprint OBJECT pprint.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        memalloc.h sysdep.h utility.h evaluatn.h moduldef.h userdata.h
        insfun.h object.h constrct.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h pprint.h)

add_library(prccode OBJECT prccode.c setup.h envrnmnt.h entities.h usrsetup.h memalloc.h
        constant.h globlpsr.h expressn.h exprnops.h constrct.h userdata.h
        moduldef.h utility.h evaluatn.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnpsr.h
        scanner.h pprint.h prcdrpsr.h prntutil.h router.h prccode.h)

add_library(prcdrfun OBJECT prcdrfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrnchk.h
        cstrnops.h exprnpsr.h scanner.h memalloc.h prcdrpsr.h router.h
        prcdrfun.h globldef.h)

add_library(prcdrpsr OBJECT prcdrpsr.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrnchk.h
        cstrnops.h cstrnutl.h exprnpsr.h scanner.h memalloc.h modulutl.h
        pprint.h prntutil.h router.h prcdrpsr.h globldef.h globlpsr.h)

add_library(prdctfun OBJECT prdctfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnpsr.h
        scanner.h router.h prdctfun.h)

add_library(prntutil OBJECT prntutil.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrcpsr.h
        strngfun.h factmngr.h tmpltdef.h factbld.h facthsh.h inscom.h
        insmngr.h memalloc.h multifun.h router.h scanner.h strngrtr.h sysdep.h
        prntutil.h)

add_library(proflfun OBJECT proflfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h classcom.h
        dffnxfun.h genrccom.h genrcfun.h memalloc.h msgcom.h msgpass.h
        router.h sysdep.h proflfun.h)

add_library(reorder OBJECT reorder.c setup.h envrnmnt.h entities.h usrsetup.h cstrnutl.h
        constrnt.h evaluatn.h constant.h extnfunc.h expressn.h exprnops.h
        constrct.h userdata.h moduldef.h utility.h insfun.h object.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h symblcmp.h cstrccom.h objrtmch.h memalloc.h pattern.h
        scanner.h reorder.h prntutil.h router.h rulelhs.h)

add_library(reteutil OBJECT reteutil.c setup.h envrnmnt.h entities.h usrsetup.h drive.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h engine.h lgcldpnd.h retract.h
        incrrset.h memalloc.h pattern.h scanner.h reorder.h prntutil.h
        router.h rulecom.h reteutil.h)

add_library(retract OBJECT retract.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h argacces.h drive.h engine.h
        lgcldpnd.h retract.h memalloc.h prntutil.h reteutil.h rulecom.h
        router.h)

add_library(router OBJECT router.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h filertr.h memalloc.h prntutil.h
        scanner.h strngrtr.h sysdep.h router.h)

add_library(rulebin OBJECT rulebin.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h bload.h exprnbin.h sysdep.h
        symblbin.h bsave.h engine.h lgcldpnd.h retract.h memalloc.h pattern.h
        scanner.h reorder.h reteutil.h rulecom.h rulebsc.h rulebin.h
        cstrcbin.h modulbin.h)

add_library(rulebld OBJECT rulebld.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        constrct.h userdata.h moduldef.h utility.h evaluatn.h insfun.h
        object.h constrnt.h expressn.h exprnops.h multifld.h symbol.h match.h
        network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h drive.h incrrset.h memalloc.h
        pattern.h scanner.h reorder.h prntutil.h reteutil.h rulecom.h router.h
        rulebld.h rulepsr.h watch.h)

add_library(rulebsc OBJECT rulebsc.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h drive.h engine.h lgcldpnd.h retract.h
        reteutil.h rulecom.h router.h watch.h rulebin.h cstrcbin.h modulbin.h
        rulecmp.h rulebsc.h)

add_library(rulecmp OBJECT rulecmp.c setup.h envrnmnt.h entities.h usrsetup.h factbld.h
        network.h match.h ruledef.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h objrtmch.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h pattern.h scanner.h
        reorder.h reteutil.h rulecom.h rulecmp.h)

add_library(rulecom OBJECT rulecom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h engine.h lgcldpnd.h retract.h
        incrrset.h memalloc.h pattern.h scanner.h reorder.h prntutil.h
        reteutil.h rulecom.h router.h ruledlt.h sysdep.h watch.h rulebin.h
        cstrcbin.h modulbin.h)

add_library(rulecstr OBJECT rulecstr.c setup.h envrnmnt.h entities.h usrsetup.h
        analysis.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h reorder.h
        pattern.h scanner.h cstrnchk.h cstrnops.h cstrnutl.h prcdrpsr.h
        prntutil.h router.h rulepsr.h rulecstr.h)

add_library(ruledef OBJECT ruledef.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h drive.h engine.h lgcldpnd.h retract.h
        memalloc.h pattern.h scanner.h reorder.h reteutil.h rulecom.h
        rulebsc.h rulepsr.h ruledlt.h bload.h exprnbin.h sysdep.h symblbin.h
        rulebin.h cstrcbin.h modulbin.h rulecmp.h)

add_library(ruledlt OBJECT ruledlt.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h bload.h exprnbin.h sysdep.h
        symblbin.h drive.h engine.h lgcldpnd.h retract.h memalloc.h pattern.h
        scanner.h reorder.h reteutil.h rulecom.h ruledlt.h)

add_library(rulelhs OBJECT rulelhs.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h
        ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h objrtmch.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h crstrtgy.h argacces.h cstrnchk.h exprnpsr.h
        scanner.h memalloc.h pattern.h reorder.h pprint.h prntutil.h router.h
        rulelhs.h)

add_library(rulepsr OBJECT rulepsr.c setup.h envrnmnt.h entities.h usrsetup.h analysis.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h reorder.h pattern.h scanner.h
        cstrcpsr.h strngfun.h cstrnchk.h cstrnops.h engine.h lgcldpnd.h
        retract.h exprnpsr.h incrrset.h memalloc.h modulutl.h prccode.h
        prcdrpsr.h pprint.h prntutil.h router.h rulebld.h rulebsc.h rulecstr.h
        ruledlt.h rulelhs.h watch.h tmpltfun.h factmngr.h tmpltdef.h factbld.h
        facthsh.h bload.h exprnbin.h sysdep.h symblbin.h rulepsr.h)

add_library(scanner OBJECT scanner.c setup.h envrnmnt.h entities.h usrsetup.h constant.h
        memalloc.h pprint.h prntutil.h router.h symbol.h sysdep.h utility.h
        evaluatn.h moduldef.h userdata.h insfun.h object.h constrct.h
        constrnt.h expressn.h exprnops.h multifld.h match.h network.h
        ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h symblcmp.h
        cstrccom.h objrtmch.h scanner.h)

add_library(sortfun OBJECT sortfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h dffnxfun.h memalloc.h sysdep.h
        sortfun.h)

add_library(strngfun OBJECT strngfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h commline.h
        cstrcpsr.h strngfun.h engine.h lgcldpnd.h retract.h exprnpsr.h
        scanner.h memalloc.h miscfun.h prcdrpsr.h pprint.h prntutil.h router.h
        strngrtr.h sysdep.h drive.h)

add_library(strngrtr OBJECT strngrtr.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h memalloc.h prntutil.h router.h sysdep.h strngrtr.h
        utility.h evaluatn.h moduldef.h userdata.h insfun.h object.h
        constrct.h constrnt.h expressn.h exprnops.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h)

add_library(symblbin OBJECT symblbin.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h bload.h
        exprnbin.h sysdep.h symblbin.h bsave.h cstrnbin.h exprnpsr.h scanner.h
        memalloc.h router.h)

add_library(symblcmp OBJECT symblcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrncmp.h
        exprnpsr.h scanner.h memalloc.h prntutil.h router.h sysdep.h)

add_library(symbol OBJECT symbol.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h memalloc.h prntutil.h router.h
        sysdep.h)

add_library(sysdep OBJECT sysdep.c setup.h envrnmnt.h entities.h usrsetup.h memalloc.h
        sysdep.h)

add_library(textpro OBJECT textpro.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h commline.h memalloc.h prntutil.h
        router.h sysdep.h textpro.h)

add_library(tmpltbin OBJECT tmpltbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h bsave.h cstrnbin.h factbin.h factbld.h factmngr.h
        tmpltdef.h facthsh.h memalloc.h tmpltpsr.h tmpltutl.h tmpltbin.h
        cstrcbin.h modulbin.h)

add_library(tmpltbsc OBJECT tmpltbsc.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrcpsr.h
        strngfun.h factrhs.h factmngr.h tmpltdef.h factbld.h facthsh.h
        scanner.h memalloc.h router.h tmpltbin.h cstrcbin.h modulbin.h
        tmpltcmp.h tmpltpsr.h tmpltutl.h tmpltbsc.h)

add_library(tmpltcmp OBJECT tmpltcmp.c setup.h envrnmnt.h entities.h usrsetup.h
        conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        cstrccom.h objrtmch.h extnfunc.h symblcmp.h cstrncmp.h factcmp.h
        pattern.h scanner.h reorder.h tmpltdef.h factbld.h tmpltcmp.h)

add_library(tmpltdef OBJECT tmpltdef.c setup.h envrnmnt.h entities.h usrsetup.h
        cstrccom.h moduldef.h userdata.h constrct.h utility.h evaluatn.h
        constant.h insfun.h object.h constrnt.h expressn.h exprnops.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h objrtmch.h cstrnchk.h memalloc.h
        modulpsr.h scanner.h modulutl.h pattern.h reorder.h router.h
        tmpltbsc.h tmpltdef.h factbld.h tmpltfun.h factmngr.h facthsh.h
        tmpltpsr.h tmpltutl.h bload.h exprnbin.h sysdep.h symblbin.h
        tmpltbin.h cstrcbin.h modulbin.h tmpltcmp.h)

add_library(tmpltfun OBJECT tmpltfun.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h commline.h
        cstrnchk.h default.h exprnpsr.h scanner.h factmngr.h tmpltdef.h
        factbld.h facthsh.h factrhs.h memalloc.h modulutl.h pprint.h
        prcdrpsr.h prntutil.h reorder.h pattern.h router.h sysdep.h tmpltlhs.h
        tmpltrhs.h tmpltutl.h tmpltfun.h)

add_library(tmpltlhs OBJECT tmpltlhs.c setup.h envrnmnt.h entities.h usrsetup.h
        constant.h constrct.h userdata.h moduldef.h utility.h evaluatn.h
        insfun.h object.h constrnt.h expressn.h exprnops.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h exprnpsr.h scanner.h factrhs.h
        factmngr.h tmpltdef.h factbld.h facthsh.h memalloc.h modulutl.h
        pattern.h reorder.h pprint.h prntutil.h router.h tmpltutl.h tmpltlhs.h)

add_library(tmpltpsr OBJECT tmpltpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h
        utility.h evaluatn.h constant.h moduldef.h userdata.h insfun.h
        object.h constrct.h constrnt.h expressn.h exprnops.h multifld.h
        symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h
        extnfunc.h symblcmp.h cstrccom.h objrtmch.h exprnbin.h sysdep.h
        symblbin.h cstrcpsr.h strngfun.h cstrnchk.h cstrnpsr.h cstrnutl.h
        default.h exprnpsr.h scanner.h factmngr.h tmpltdef.h factbld.h
        facthsh.h memalloc.h modulutl.h pattern.h reorder.h pprint.h
        prntutil.h router.h tmpltbsc.h watch.h tmpltpsr.h)

add_library(tmpltrhs OBJECT tmpltrhs.c setup.h envrnmnt.h entities.h usrsetup.h default.h
        constrnt.h evaluatn.h constant.h extnfunc.h expressn.h exprnops.h
        constrct.h userdata.h moduldef.h utility.h insfun.h object.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h symblcmp.h cstrccom.h objrtmch.h factrhs.h factmngr.h
        tmpltdef.h factbld.h facthsh.h scanner.h memalloc.h modulutl.h
        pprint.h prntutil.h router.h tmpltfun.h tmpltlhs.h tmpltutl.h
        tmpltrhs.h)

add_library(tmpltutl OBJECT tmpltutl.c setup.h envrnmnt.h entities.h usrsetup.h
        argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h
        utility.h evaluatn.h constant.h insfun.h object.h constrnt.h
        multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h
        conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h cstrnchk.h
        memalloc.h modulutl.h scanner.h prntutil.h router.h sysdep.h
        tmpltbsc.h tmpltdef.h factbld.h tmpltfun.h factmngr.h facthsh.h
        tmpltpsr.h watch.h tmpltutl.h)

add_library(userdata OBJECT userdata.c setup.h envrnmnt.h entities.h usrsetup.h
        userdata.h)

add_library(userfunctions OBJECT userfunctions.c clips.h setup.h envrnmnt.h entities.h
        usrsetup.h argacces.h expressn.h exprnops.h constrct.h userdata.h
        moduldef.h utility.h evaluatn.h constant.h insfun.h object.h
        constrnt.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h objrtmch.h
        memalloc.h cstrcpsr.h strngfun.h fileutil.h envrnbld.h commline.h
        prntutil.h router.h filertr.h strngrtr.h iofun.h sysdep.h bmathfun.h
        exprnpsr.h scanner.h miscfun.h watch.h modulbsc.h bload.h exprnbin.h
        symblbin.h bsave.h rulebsc.h engine.h lgcldpnd.h retract.h drive.h
        incrrset.h rulecom.h dffctdef.h dffctbsc.h tmpltdef.h factbld.h
        tmpltbsc.h tmpltfun.h factmngr.h facthsh.h factcom.h factfile.h
        factfun.h globldef.h globlbsc.h globlcom.h dffnxfun.h genrccom.h
        genrcfun.h classcom.h classexm.h classfun.h classinf.h classini.h
        classpsr.h defins.h inscom.h insfile.h insmngr.h msgcom.h msgpass.h)

add_library(utility OBJECT utility.c setup.h envrnmnt.h entities.h usrsetup.h commline.h
        evaluatn.h constant.h factmngr.h conscomp.h constrct.h userdata.h
        moduldef.h utility.h insfun.h object.h constrnt.h expressn.h
        exprnops.h multifld.h symbol.h match.h network.h ruledef.h agenda.h
        crstrtgy.h cstrccom.h objrtmch.h extnfunc.h symblcmp.h tmpltdef.h
        factbld.h facthsh.h memalloc.h prntutil.h router.h sysdep.h)

add_library(watch OBJECT watch.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h
        expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h
        evaluatn.h constant.h insfun.h object.h constrnt.h multifld.h symbol.h
        match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h
        symblcmp.h cstrccom.h objrtmch.h memalloc.h router.h watch.h)



# public headers to install (all CLIPS headers; clips.h transitively includes the rest)
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

if(WIN32)

    add_library(clips SHARED )
    target_link_libraries(clips ${OBJNAMES})
    add_library(clips-static ${OBJNAMES})
    target_link_libraries(clips-static ${OBJNAMES})
    add_executable(clipscli)
    if(static-cli)
        set_property(TARGET clipscli PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")  # static link MSVC Runtime
        target_link_libraries(clipscli main clips-static)
    else()
        target_link_libraries(clipscli main clips)
    endif()
    install(FILES ${HEADER_FILES} DESTINATION include/clips-641)
    install(TARGETS clipscli clips clips-static
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)

else()

    add_library(clips SHARED )
    target_link_libraries(clips ${OBJNAMES})
    add_library(clips-static ${OBJNAMES})
    target_link_libraries(clips-static ${OBJNAMES} )
    set_target_properties(clips PROPERTIES LINK_FLAGS_RELEASE -s)
    set_target_properties(clips-static PROPERTIES LINK_FLAGS_RELEASE -s)
    target_link_libraries(clips m)
    target_link_libraries(clips-static m)
    if(static-cli)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(BUILD_SHARED_LIBS OFF)
        set(CMAKE_EXE_LINKER_FLAGS "-static -s")
        add_executable(clipscli)
        target_link_libraries(clipscli main clips-static)
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-s")
        add_executable(clipscli)
        target_link_libraries(clipscli main clips )
        target_compile_options(clipscli PUBLIC "-fpic")
    endif()
    install(FILES ${HEADER_FILES} DESTINATION include/clips-641)
    install(TARGETS clipscli clips clips-static
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()
