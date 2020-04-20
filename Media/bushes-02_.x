xof 0303txt 0032
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}


Material bridge {
 0.588000;0.588000;0.588000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "bridge.tga";
 }
}

Material tree04 {
 0.588000;0.588000;0.588000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "tree04.tga";
 }
}

Material plant02 {
 0.588000;0.588000;0.588000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "plant02.tga";
 }
}

Material plant01 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "plant01.tga";
 }
}

Material hedge {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "hedge.tga";
 }
}

Material lighter {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "lighter.tga";
 }
}

Material bench {
 0.588000;0.588000;0.588000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "bench.tga";
 }
}

Material tree-01_barkSub0 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "bark.tga";
 }
}

Material tree-01_tree01Sub1 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "tree01.tga";
 }
}

Material tree-02_barkSub0 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "bark.tga";
 }
}

Material tree-02_tree02Sub1 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "tree02.tga";
 }
}

Material tree-03_barkSub0 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "bark.tga";
 }
}

Material tree-03_tree03Sub1 {
 0.588235;0.588235;0.588235;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "tree03.tga";
 }
}

Material fence {
 0.588000;0.588000;0.588000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "fence.tga";
 }
}

Frame bushes-02_ {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,9.411572,-0.000000,1.000000;;
  }

  Mesh  {
   48;
   16.777678;8.802543;-3.051468;,
   -13.398170;9.488482;-28.003632;,
   -3.738649;9.135955;-2.887090;,
   -13.398170;9.488482;-28.003632;,
   16.777678;8.802543;-3.051468;,
   6.200959;8.835479;-36.476192;,
   -14.337975;8.771060;23.256886;,
   -4.462125;-9.488482;-2.881274;,
   -14.814012;-9.488482;23.286764;,
   -4.462125;-9.488482;-2.881274;,
   -14.337975;8.771060;23.256886;,
   -3.738649;9.135955;-2.887090;,
   17.191584;-9.488481;-3.054784;,
   6.200959;8.835479;-36.476192;,
   16.777678;8.802543;-3.051468;,
   6.200959;8.835479;-36.476192;,
   17.191584;-9.488481;-3.054784;,
   6.551136;-9.488479;-36.866302;,
   -14.814012;-9.488482;23.286764;,
   4.047483;8.771060;33.168987;,
   -14.337975;8.771060;23.256886;,
   4.047483;8.771060;33.168987;,
   -14.814012;-9.488482;23.286764;,
   4.077384;-9.488481;33.645145;,
   6.200959;8.835479;-36.476192;,
   -14.229190;-9.488482;-27.077713;,
   -13.398170;9.488482;-28.003632;,
   -14.229190;-9.488482;-27.077713;,
   6.200959;8.835479;-36.476192;,
   6.551136;-9.488479;-36.866302;,
   4.047483;8.771060;33.168987;,
   -3.738649;9.135955;-2.887090;,
   -14.337975;8.771060;23.256886;,
   -3.738649;9.135955;-2.887090;,
   4.047483;8.771060;33.168987;,
   16.777678;8.802543;-3.051468;,
   -14.229190;-9.488482;-27.077713;,
   -3.738649;9.135955;-2.887090;,
   -13.398170;9.488482;-28.003632;,
   -3.738649;9.135955;-2.887090;,
   -14.229190;-9.488482;-27.077713;,
   -4.462125;-9.488482;-2.881274;,
   17.191584;-9.488481;-3.054784;,
   4.047483;8.771060;33.168987;,
   4.077384;-9.488481;33.645145;,
   4.047483;8.771060;33.168987;,
   17.191584;-9.488481;-3.054784;,
   16.777678;8.802543;-3.051468;;
   16;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;,
   3;36,37,38;,
   3;39,40,41;,
   3;42,43,44;,
   3;45,46,47;;

   MeshNormals  {
    48;
    0.764383;0.644611;0.013993;,
    -0.728738;0.598022;-0.333631;,
    -0.576723;0.816917;0.006126;,
    -0.728738;0.598022;-0.333631;,
    0.764383;0.644611;0.013993;,
    0.335449;0.569878;-0.750142;,
    -0.757908;0.589186;0.280064;,
    -0.999337;0.036386;0.000861;,
    -0.940674;0.027547;0.338191;,
    -0.999337;0.036386;0.000861;,
    -0.757908;0.589186;0.280064;,
    -0.576723;0.816917;0.006126;,
    0.999631;0.021469;0.016637;,
    0.335449;0.569878;-0.750142;,
    0.764383;0.644611;0.013993;,
    0.335449;0.569878;-0.750142;,
    0.999631;0.021469;0.016637;,
    0.404925;0.027196;-0.913946;,
    -0.940674;0.027547;0.338191;,
    0.294686;0.575820;0.762621;,
    -0.757908;0.589186;0.280064;,
    0.294686;0.575820;0.762621;,
    -0.940674;0.027547;0.338191;,
    0.351556;0.024980;0.935833;,
    0.335449;0.569878;-0.750142;,
    -0.935442;0.028674;-0.352316;,
    -0.728738;0.598022;-0.333631;,
    -0.935442;0.028674;-0.352316;,
    0.335449;0.569878;-0.750142;,
    0.404925;0.027196;-0.913946;,
    0.294686;0.575820;0.762621;,
    -0.576723;0.816917;0.006126;,
    -0.757908;0.589186;0.280064;,
    -0.576723;0.816917;0.006126;,
    0.294686;0.575820;0.762621;,
    0.764383;0.644611;0.013993;,
    -0.935442;0.028674;-0.352316;,
    -0.576723;0.816917;0.006126;,
    -0.728738;0.598022;-0.333631;,
    -0.576723;0.816917;0.006126;,
    -0.935442;0.028674;-0.352316;,
    -0.999337;0.036386;0.000861;,
    0.999631;0.021469;0.016637;,
    0.294686;0.575820;0.762621;,
    0.351556;0.024980;0.935833;,
    0.294686;0.575820;0.762621;,
    0.999631;0.021469;0.016637;,
    0.764383;0.644611;0.013993;;
    16;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;;
   }

   MeshMaterialList  {
    1;
    16;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;
    { hedge }
   }

   MeshTextureCoords  {
    48;
    3.977193;-0.469829;,
    2.950529;0.896915;,
    3.213831;-0.168504;,
    2.950529;0.896915;,
    3.977193;-0.469829;,
    3.783126;1.087277;,
    -0.803528;0.143371;,
    -0.157878;0.873753;,
    -0.801233;0.873753;,
    -0.157878;0.873753;,
    -0.803528;0.143371;,
    -0.168504;0.128775;,
    1.475906;0.873753;,
    -0.087277;0.140794;,
    1.469829;0.142112;,
    -0.087277;0.140794;,
    1.475906;0.873753;,
    -0.100067;0.873753;,
    -0.801233;0.873753;,
    -1.425634;0.143371;,
    -0.803528;0.143371;,
    -1.425634;0.143371;,
    -0.801233;0.873753;,
    -1.444580;0.873753;,
    3.783126;0.140794;,
    2.911093;0.873753;,
    2.950529;0.114674;,
    2.911093;0.873753;,
    3.783126;0.140794;,
    3.799740;0.873753;,
    3.136044;-1.425634;,
    3.213831;-0.168504;,
    2.648439;-0.803528;,
    3.213831;-0.168504;,
    3.136044;-1.425634;,
    3.977193;-0.469829;,
    0.866555;0.873753;,
    -0.168504;0.128775;,
    0.896915;0.114674;,
    -0.168504;0.128775;,
    0.866555;0.873753;,
    -0.157878;0.873753;,
    1.475906;0.873753;,
    2.425634;0.143371;,
    2.444581;0.873753;,
    2.425634;0.143371;,
    1.475906;0.873753;,
    1.469829;0.142112;;
   }
  }
 }
}

AnimationSet Anim-1 {
 
}