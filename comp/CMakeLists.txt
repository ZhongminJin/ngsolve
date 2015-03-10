if (USE_GUI)
    add_definitions(-DTCL)
endif (USE_GUI)

if(NOT WIN32)
    set(ngcomp_object_libs $<TARGET_OBJECTS:ngmg> )
endif(NOT WIN32)

add_library( ngcomp ${NGS_LIB_TYPE}
        ${ngcomp_object_libs}
        bilinearform.cpp facetfespace.cpp fespace.cpp 
        gridfunction.cpp h1hofespace.cpp hcurlhdivfes.cpp hcurlhofespace.cpp 
        hdivfes.cpp hdivhofespace.cpp hierarchicalee.cpp l2hofespace.cpp     
        linearform.cpp meshaccess.cpp ngsobject.cpp postproc.cpp	     
        preconditioner.cpp vectorfacetfespace.cpp bddc.cpp hypre_precond.cpp 
        python_comp.cpp basenumproc.cpp pde.cpp pdeparser.cpp 
        )

if(NOT WIN32)
    target_link_libraries (ngcomp interface ngfem ngla ngbla ngstd ${TCL_LIBRARY} ${MPI_CXX_LIBRARIES} ${PYTHON_LIBS} ${LAPACK_LIBRARIES} ${MKL_LIBRARIES})
    install( TARGETS ngcomp ${ngs_install_dir})
endif(NOT WIN32)

install( FILES
        bilinearform.hpp comp.hpp facetfespace.hpp	   
        fespace.hpp gridfunction.hpp h1hofespace.hpp hcurlhdivfes.hpp	   
        hcurlhofespace.hpp hdivfes.hpp hdivhofespace.hpp		   
        l2hofespace.hpp linearform.hpp meshaccess.hpp ngsobject.hpp	   
        postproc.hpp preconditioner.hpp vectorfacetfespace.hpp hypre_precond.hpp 
        pde.hpp numproc.hpp 
        DESTINATION include
       )

