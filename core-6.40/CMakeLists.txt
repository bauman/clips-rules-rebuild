set( SOURCE_FILES
  agenda.c
  analysis.c
  argacces.c
  bload.c
  bmathfun.c
  bsave.c
  classcom.c
  classexm.c
  classfun.c
  classinf.c
  classini.c
  classpsr.c
  clsltpsr.c
  commline.c
  conscomp.c
  constrct.c
  constrnt.c
  crstrtgy.c
  cstrcbin.c
  cstrccom.c
  cstrcpsr.c
  cstrnbin.c
  cstrnchk.c
  cstrncmp.c
  cstrnops.c
  cstrnpsr.c
  cstrnutl.c
  default.c
  defins.c
  developr.c
  dffctbin.c
  dffctbsc.c
  dffctcmp.c
  dffctdef.c
  dffctpsr.c
  dffnxbin.c
  dffnxcmp.c
  dffnxexe.c
  dffnxfun.c
  dffnxpsr.c
  dfinsbin.c
  dfinscmp.c
  drive.c
  emathfun.c
  engine.c
  envrnbld.c
  envrnmnt.c
  evaluatn.c
  expressn.c
  exprnbin.c
  exprnops.c
  exprnpsr.c
  extnfunc.c
  factbin.c
  factbld.c
  factcmp.c
  factcom.c
  factfile.c
  factfun.c
  factgen.c
  facthsh.c
  factlhs.c
  factmch.c
  factmngr.c
  factprt.c
  factqpsr.c
  factqury.c
  factrete.c
  factrhs.c
  filecom.c
  filertr.c
  fileutil.c
  generate.c
  genrcbin.c
  genrccmp.c
  genrccom.c
  genrcexe.c
  genrcfun.c
  genrcpsr.c
  globlbin.c
  globlbsc.c
  globlcmp.c
  globlcom.c
  globldef.c
  globlpsr.c
  immthpsr.c
  incrrset.c
  inherpsr.c
  inscom.c
  insfile.c
  insfun.c
  insmngr.c
  insmoddp.c
  insmult.c
  inspsr.c
  insquery.c
  insqypsr.c
  iofun.c
  lgcldpnd.c
  main.c
  memalloc.c
  miscfun.c
  modulbin.c
  modulbsc.c
  modulcmp.c
  moduldef.c
  modulpsr.c
  modulutl.c
  msgcom.c
  msgfun.c
  msgpass.c
  msgpsr.c
  multifld.c
  multifun.c
  objbin.c
  objcmp.c
  objrtbin.c
  objrtbld.c
  objrtcmp.c
  objrtfnx.c
  objrtgen.c
  objrtmch.c
  parsefun.c
  pattern.c
  pprint.c
  prccode.c
  prcdrfun.c
  prcdrpsr.c
  prdctfun.c
  prntutil.c
  proflfun.c
  reorder.c
  reteutil.c
  retract.c
  router.c
  rulebin.c
  rulebld.c
  rulebsc.c
  rulecmp.c
  rulecom.c
  rulecstr.c
  ruledef.c
  ruledlt.c
  rulelhs.c
  rulepsr.c
  scanner.c
  sortfun.c
  strngfun.c
  strngrtr.c
  symblbin.c
  symblcmp.c
  symbol.c
  sysdep.c
  textpro.c
  tmpltbin.c
  tmpltbsc.c
  tmpltcmp.c
  tmpltdef.c
  tmpltfun.c
  tmpltlhs.c
  tmpltpsr.c
  tmpltrhs.c
  tmpltutl.c
  userdata.c
  userfunctions.c
  utility.c
  watch.c
)


if(WIN32)
    add_definitions(-DWIN_MVC=1)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    
    add_library(  clips SHARED  ${SOURCE_FILES})
    add_library(  clips-static  ${SOURCE_FILES} )
    add_executable(clipscli main.c)

    if(static-cli)
        set_property(TARGET clipscli PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")  # static link MSVC Runtime
        target_link_libraries(clipscli clips-static )
    else()
        target_link_libraries(clipscli clips )
    endif()
    
    install(TARGETS clipscli clips clips-static
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
    
else()

    
    add_library(clips SHARED ${SOURCE_FILES})
    add_library(clips-static ${SOURCE_FILES})
    set_target_properties(clips PROPERTIES LINK_FLAGS_RELEASE -s)
    set_target_properties(clips-static PROPERTIES LINK_FLAGS_RELEASE -s)
    target_link_libraries(clips m)
    target_link_libraries(clips-static m)
    add_executable(clipscli main.c)
    if(static-cli)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(BUILD_SHARED_LIBS OFF)
        set(CMAKE_EXE_LINKER_FLAGS "-static -s")
        target_link_libraries(clipscli clips-static )
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-s")
        target_link_libraries(clipscli clips )
    endif()
    install(FILES ${HEADER_FILES} DESTINATION include)
    install(TARGETS clipscli clips clips-static
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()