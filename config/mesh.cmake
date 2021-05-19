set(MESH_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh)

set(MESH_SOURCES
    ${MESH_SOURCE_DIR}/meshSetup.cpp
    ${MESH_SOURCE_DIR}/meshNekReader.cpp
    ${MESH_SOURCE_DIR}/meshPhysicalNodesHex3D.cpp
    ${MESH_SOURCE_DIR}/meshGlobalIds.cpp
    ${MESH_SOURCE_DIR}/meshBasis1D.cpp
    ${MESH_SOURCE_DIR}/meshBasisHex3D.cpp
    ${MESH_SOURCE_DIR}/meshApplyElementMatrix.cpp
    ${MESH_SOURCE_DIR}/meshConnect.cpp
    ${MESH_SOURCE_DIR}/meshConnectBoundary.cpp
    ${MESH_SOURCE_DIR}/meshConnectFaceNodes3D.cpp
    ${MESH_SOURCE_DIR}/meshConnectPeriodicFaceNodes3D.cpp
    ${MESH_SOURCE_DIR}/meshFree.cpp
    ${MESH_SOURCE_DIR}/meshMove.cpp
    ${MESH_SOURCE_DIR}/meshGeometricFactorsHex3D.cpp
    ${MESH_SOURCE_DIR}/meshHaloExchange.cpp
    ${MESH_SOURCE_DIR}/meshHaloExtract.cpp
    ${MESH_SOURCE_DIR}/meshHaloSetup.cpp
    ${MESH_SOURCE_DIR}/meshLoadReferenceNodesHex3D.cpp
    ${MESH_SOURCE_DIR}/meshOccaSetup3D.cpp
    ${MESH_SOURCE_DIR}/meshParallelConsecutiveGlobalNumbering.cpp
    ${MESH_SOURCE_DIR}/meshParallelGatherScatterSetup.cpp
    ${MESH_SOURCE_DIR}/meshSurfaceGeometricFactorsHex3D.cpp
    ${MESH_SOURCE_DIR}/meshParallelConnectOpt.cpp)
