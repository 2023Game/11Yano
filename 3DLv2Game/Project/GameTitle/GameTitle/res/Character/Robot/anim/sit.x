xof 0303txt 0032

template XSkinMeshHeader {
  <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
  WORD nMaxSkinWeightsPerVertex;
  WORD nMaxSkinWeightsPerFace;
  WORD nBones;
}

template SkinWeights {
  <6f0d123b-bad2-4167-a0d0-80224f25fabb>
  STRING transformNodeName;
  DWORD nWeights;
  array DWORD vertexIndices[nWeights];
  array float weights[nWeights];
  Matrix4x4 matrixOffset;
}

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000,-1.000000, 0.000000,
     0.000000, 1.000000,-0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame ROBOT_SOLDIER_RIG {
    FrameTransformMatrix {
       0.100000, 0.000000, 0.000000, 0.000000,
       0.000000,-0.000000, 0.100000, 0.000000,
       0.000000,-0.100000,-0.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Frame ROBOT_SOLDIER_RIG_Hips {
      FrameTransformMatrix {
         0.922941, 0.149853, 0.354577, 0.000000,
         0.114847, 0.771972,-0.625195, 0.000000,
        -0.367411, 0.617740, 0.695274, 0.000000,
         3.508505,17.198601,-1.709373, 1.000000;;
      }
      Frame ROBOT_SOLDIER_RIG_LeftUpLeg {
        FrameTransformMatrix {
           0.717568, 0.223313,-0.659718, 0.000000,
          -0.596072,-0.293056,-0.747540, 0.000000,
          -0.360270, 0.929650,-0.077177, 0.000000,
          12.894799,-9.482498,-0.055401, 1.000000;;
        }
        Frame ROBOT_SOLDIER_RIG_LeftLeg {
          FrameTransformMatrix {
             0.995159,-0.010856,-0.097671, 0.000000,
             0.092150,-0.242242, 0.965830, 0.000000,
            -0.034145,-0.970155,-0.240069, 0.000000,
             0.244693,-40.595406,-0.516993, 1.000000;;
          }
          Frame ROBOT_SOLDIER_RIG_LeftFoot {
            FrameTransformMatrix {
               0.971380,-0.021536, 0.236554, 0.000000,
              -0.079369, 0.909214, 0.408693, 0.000000,
              -0.223880,-0.415772, 0.881483, 0.000000,
              -0.244698,-42.048004,-2.057602, 1.000000;;
            }
            Frame ROBOT_SOLDIER_RIG_LeftToeBase {
              FrameTransformMatrix {
                 0.999598, 0.027768,-0.005693, 0.000000,
                -0.028345, 0.978902,-0.202356, 0.000000,
                -0.000046, 0.202437, 0.979295, 0.000000,
                 0.373402,-10.492208,12.640696, 1.000000;;
              }
              Frame ROBOT_SOLDIER_RIG_LeftToe_End {
                FrameTransformMatrix {
                   1.000000,-0.000000, 0.000000, 0.000000,
                   0.000000, 1.000000, 0.000000, 0.000000,
                  -0.000000,-0.000000, 1.000000, 0.000000,
                  -0.000002,-0.000004, 9.992504, 1.000000;;
                }
                Frame ROBOT_SOLDIER_RIG_LeftToe_End_end {
                  FrameTransformMatrix {
                     1.000000,-0.000000, 0.000000, 0.000000,
                     0.000000, 1.000000, 0.000000, 0.000000,
                     0.000000,-0.000000, 1.000000, 0.000000,
                     0.000004, 9.992497,-0.000002, 1.000000;;
                  }
                } // End of ROBOT_SOLDIER_RIG_LeftToe_End_end
              } // End of ROBOT_SOLDIER_RIG_LeftToe_End
            } // End of ROBOT_SOLDIER_RIG_LeftToeBase
          } // End of ROBOT_SOLDIER_RIG_LeftFoot
        } // End of ROBOT_SOLDIER_RIG_LeftLeg
      } // End of ROBOT_SOLDIER_RIG_LeftUpLeg
      Frame ROBOT_SOLDIER_RIG_RightUpLeg {
        FrameTransformMatrix {
           0.977358, 0.173853,-0.120610, 0.000000,
          -0.117389,-0.028731,-0.992670, 0.000000,
          -0.176044, 0.984352,-0.007672, 0.000000,
          -12.894800,-9.482503,-0.055399, 1.000000;;
        }
        Frame ROBOT_SOLDIER_RIG_RightLeg {
          FrameTransformMatrix {
             0.977046,-0.203864, 0.061811, 0.000000,
            -0.033848, 0.137905, 0.989867, 0.000000,
            -0.210322,-0.969238, 0.127839, 0.000000,
            -0.244694,-40.595402,-0.516990, 1.000000;;
          }
          Frame ROBOT_SOLDIER_RIG_RightFoot {
            FrameTransformMatrix {
               0.992747, 0.117433,-0.025744, 0.000000,
              -0.110884, 0.811647,-0.573528, 0.000000,
              -0.046456, 0.572223, 0.818781, 0.000000,
               0.244700,-42.048012,-2.057609, 1.000000;;
            }
            Frame ROBOT_SOLDIER_RIG_RightToeBase {
              FrameTransformMatrix {
                 0.999980, 0.005332, 0.003352, 0.000000,
                -0.005358, 0.999955, 0.007834, 0.000000,
                -0.003310,-0.007852, 0.999964, 0.000000,
                -0.373398,-10.492219,12.640696, 1.000000;;
              }
              Frame ROBOT_SOLDIER_RIG_RightToe_End {
                FrameTransformMatrix {
                   1.000000,-0.000000,-0.000000, 0.000000,
                  -0.000000, 1.000000, 0.000000, 0.000000,
                   0.000000,-0.000000, 1.000000, 0.000000,
                   0.000000,-0.000001, 9.992503, 1.000000;;
                }
                Frame ROBOT_SOLDIER_RIG_RightToe_End_end {
                  FrameTransformMatrix {
                     1.000000, 0.000000,-0.000000, 0.000000,
                    -0.000000, 1.000000, 0.000000, 0.000000,
                     0.000000,-0.000000, 1.000000, 0.000000,
                    -0.000002, 9.992506,-0.000002, 1.000000;;
                  }
                } // End of ROBOT_SOLDIER_RIG_RightToe_End_end
              } // End of ROBOT_SOLDIER_RIG_RightToe_End
            } // End of ROBOT_SOLDIER_RIG_RightToeBase
          } // End of ROBOT_SOLDIER_RIG_RightFoot
        } // End of ROBOT_SOLDIER_RIG_RightLeg
      } // End of ROBOT_SOLDIER_RIG_RightUpLeg
      Frame ROBOT_SOLDIER_RIG_Spine {
        FrameTransformMatrix {
           0.988192,-0.141048,-0.059852, 0.000000,
           0.152558, 0.869406, 0.469957, 0.000000,
          -0.014251,-0.473539, 0.880658, 0.000000,
          -0.000000,13.395802,-1.227298, 1.000000;;
        }
        Frame ROBOT_SOLDIER_RIG_Spine1 {
          FrameTransformMatrix {
             0.997608, 0.028541, 0.062955, 0.000000,
            -0.045600, 0.956216, 0.289088, 0.000000,
            -0.051948,-0.291267, 0.955230, 0.000000,
            -0.000100,13.655706,-1.422300, 1.000000;;
          }
          Frame ROBOT_SOLDIER_RIG_Spine2 {
            FrameTransformMatrix {
               0.997262, 0.043197, 0.060019, 0.000000,
              -0.058845, 0.955113, 0.290338, 0.000000,
              -0.044783,-0.293075, 0.955040, 0.000000,
               0.000100,13.360202,-1.626499, 1.000000;;
            }
            Frame ROBOT_SOLDIER_RIG_LeftShoulder {
              FrameTransformMatrix {
                 0.661838, 0.667523, 0.341150, 0.000000,
                -0.699286, 0.713727,-0.039909, 0.000000,
                -0.270128,-0.212149, 0.939161, 0.000000,
                21.496601, 2.870901, 0.705600, 1.000000;;
              }
              Frame ROBOT_SOLDIER_RIG_LeftArm {
                FrameTransformMatrix {
                  -0.600659,-0.792674, 0.104289, 0.000000,
                   0.240113,-0.054433, 0.969218, 0.000000,
                  -0.762597, 0.607211, 0.223028, 0.000000,
                  12.978003, 0.690194,-1.526495, 1.000000;;
                }
                Frame ROBOT_SOLDIER_RIG_LeftForeArm {
                  FrameTransformMatrix {
                     0.972603, 0.230175,-0.032610, 0.000000,
                    -0.145782, 0.494615,-0.856798, 0.000000,
                    -0.181084, 0.838079, 0.514619, 0.000000,
                    31.225210,-0.028202, 0.000004, 1.000000;;
                  }
                  Frame ROBOT_SOLDIER_RIG_LeftHand {
                    FrameTransformMatrix {
                       0.372547,-0.336325,-0.864925, 0.000000,
                      -0.923748,-0.045133,-0.380333, 0.000000,
                       0.088878, 0.940664,-0.327494, 0.000000,
                      31.363201,-0.000007, 0.000001, 1.000000;;
                    }
                    Frame ROBOT_SOLDIER_RIG_LeftHandIndex1 {
                      FrameTransformMatrix {
                         0.980333,-0.101144, 0.169460, 0.000000,
                         0.085182, 0.991438, 0.098971, 0.000000,
                        -0.178019,-0.082590, 0.980555, 0.000000,
                        13.672699, 0.151797, 4.666800, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_LeftHandIndex2 {
                        FrameTransformMatrix {
                           0.964235,-0.263713, 0.026580, 0.000000,
                           0.264567, 0.951581,-0.156515, 0.000000,
                           0.015982, 0.157949, 0.987318, 0.000000,
                           5.537905, 0.000001, 0.000004, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_LeftHandIndex3 {
                          FrameTransformMatrix {
                             0.977186,-0.212021,-0.012407, 0.000000,
                             0.212024, 0.977264,-0.001087, 0.000000,
                             0.012355,-0.001568, 0.999923, 0.000000,
                             4.575105,-0.000000,-0.000003, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_LeftHandIndex4 {
                            FrameTransformMatrix {
                               1.000000,-0.000000, 0.000000, 0.000000,
                               0.000000, 1.000000, 0.000000, 0.000000,
                              -0.000000,-0.000000, 1.000000, 0.000000,
                               4.103002,-0.000001,-0.000004, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_LeftHandIndex4_end {
                              FrameTransformMatrix {
                                 1.000000, 0.000000,-0.000000, 0.000000,
                                 0.000000, 1.000000,-0.000000, 0.000000,
                                -0.000000, 0.000000, 1.000000, 0.000000,
                                 0.000001, 4.103001,-0.000000, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_LeftHandIndex4_end
                          } // End of ROBOT_SOLDIER_RIG_LeftHandIndex4
                        } // End of ROBOT_SOLDIER_RIG_LeftHandIndex3
                      } // End of ROBOT_SOLDIER_RIG_LeftHandIndex2
                    } // End of ROBOT_SOLDIER_RIG_LeftHandIndex1
                    Frame ROBOT_SOLDIER_RIG_LeftHandMiddle1 {
                      FrameTransformMatrix {
                         0.996490,-0.057231, 0.061099, 0.000000,
                         0.061900, 0.995070,-0.077481, 0.000000,
                        -0.056363, 0.080991, 0.995120, 0.000000,
                        13.845897, 0.130694, 1.509796, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_LeftHandMiddle2 {
                        FrameTransformMatrix {
                           0.952582,-0.304068,-0.011380, 0.000000,
                           0.303327, 0.951890,-0.043578, 0.000000,
                           0.024083, 0.038060, 0.998985, 0.000000,
                           6.632604, 0.000001, 0.000001, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_LeftHandMiddle3 {
                          FrameTransformMatrix {
                             0.986576,-0.162992,-0.010092, 0.000000,
                             0.162995, 0.986627,-0.000489, 0.000000,
                             0.010037,-0.001162, 0.999949, 0.000000,
                             4.460296,-0.000001, 0.000003, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_LeftHandMiddle4 {
                            FrameTransformMatrix {
                               1.000000, 0.000000, 0.000000, 0.000000,
                              -0.000000, 1.000000, 0.000000, 0.000000,
                              -0.000000, 0.000000, 1.000000, 0.000000,
                               4.718607,-0.000000, 0.000003, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_LeftHandMiddle4_end {
                              FrameTransformMatrix {
                                 1.000000,-0.000000, 0.000000, 0.000000,
                                 0.000000, 1.000000,-0.000000, 0.000000,
                                -0.000000,-0.000000, 1.000000, 0.000000,
                                 0.000006, 4.718601, 0.000001, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_LeftHandMiddle4_end
                          } // End of ROBOT_SOLDIER_RIG_LeftHandMiddle4
                        } // End of ROBOT_SOLDIER_RIG_LeftHandMiddle3
                      } // End of ROBOT_SOLDIER_RIG_LeftHandMiddle2
                    } // End of ROBOT_SOLDIER_RIG_LeftHandMiddle1
                    Frame ROBOT_SOLDIER_RIG_LeftHandPinky1 {
                      FrameTransformMatrix {
                         0.998128,-0.058170, 0.018892, 0.000000,
                         0.060524, 0.894970,-0.442002, 0.000000,
                         0.008803, 0.442318, 0.896815, 0.000000,
                        13.950800,-0.226408,-4.916303, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_LeftHandPinky2 {
                        FrameTransformMatrix {
                           0.947907,-0.296507,-0.116432, 0.000000,
                           0.307919, 0.946509, 0.096470, 0.000000,
                           0.081599,-0.127296, 0.988503, 0.000000,
                           4.250996, 0.000001, 0.000001, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_LeftHandPinky3 {
                          FrameTransformMatrix {
                             0.995637,-0.090034,-0.024508, 0.000000,
                             0.090035, 0.995938,-0.001092, 0.000000,
                             0.024506,-0.001119, 0.999699, 0.000000,
                             2.821101, 0.000001,-0.000003, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_LeftHandPinky4 {
                            FrameTransformMatrix {
                               1.000000,-0.000000, 0.000000, 0.000000,
                               0.000000, 1.000000,-0.000000, 0.000000,
                              -0.000000,-0.000000, 1.000000, 0.000000,
                               3.367102, 0.000002, 0.000002, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_LeftHandPinky4_end {
                              FrameTransformMatrix {
                                 1.000000,-0.000000, 0.000000, 0.000000,
                                 0.000000, 1.000000, 0.000000, 0.000000,
                                -0.000000, 0.000000, 1.000000, 0.000000,
                                -0.000003, 3.367099, 0.000001, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_LeftHandPinky4_end
                          } // End of ROBOT_SOLDIER_RIG_LeftHandPinky4
                        } // End of ROBOT_SOLDIER_RIG_LeftHandPinky3
                      } // End of ROBOT_SOLDIER_RIG_LeftHandPinky2
                    } // End of ROBOT_SOLDIER_RIG_LeftHandPinky1
                    Frame ROBOT_SOLDIER_RIG_LeftHandRing1 {
                      FrameTransformMatrix {
                         0.999793,-0.001468,-0.020289, 0.000000,
                        -0.004187, 0.961182,-0.275885, 0.000000,
                         0.019907, 0.275913, 0.960976, 0.000000,
                        14.372702, 0.009896,-1.887006, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_LeftHandRing2 {
                        FrameTransformMatrix {
                           0.939800,-0.334730,-0.068790, 0.000000,
                           0.337537, 0.940699, 0.033971, 0.000000,
                           0.053339,-0.055145, 0.997053, 0.000000,
                           5.069504, 0.000000,-0.000001, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_LeftHandRing3 {
                          FrameTransformMatrix {
                             0.981650,-0.187506,-0.034703, 0.000000,
                             0.187502, 0.982258,-0.003393, 0.000000,
                             0.034724,-0.003177, 0.999392, 0.000000,
                             3.781899,-0.000000,-0.000006, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_LeftHandRing4 {
                            FrameTransformMatrix {
                               1.000000, 0.000000,-0.000000, 0.000000,
                              -0.000000, 1.000000, 0.000000, 0.000000,
                              -0.000000, 0.000000, 1.000000, 0.000000,
                               3.804002,-0.000001,-0.000002, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_LeftHandRing4_end {
                              FrameTransformMatrix {
                                 1.000000, 0.000000,-0.000000, 0.000000,
                                 0.000000, 1.000000,-0.000000, 0.000000,
                                 0.000000, 0.000000, 1.000000, 0.000000,
                                 0.000001, 3.804002,-0.000004, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_LeftHandRing4_end
                          } // End of ROBOT_SOLDIER_RIG_LeftHandRing4
                        } // End of ROBOT_SOLDIER_RIG_LeftHandRing3
                      } // End of ROBOT_SOLDIER_RIG_LeftHandRing2
                    } // End of ROBOT_SOLDIER_RIG_LeftHandRing1
                    Frame ROBOT_SOLDIER_RIG_LeftHandThumb1 {
                      FrameTransformMatrix {
                         0.948441, 0.265083, 0.173757, 0.000000,
                        -0.219583, 0.944869,-0.242910, 0.000000,
                        -0.228569, 0.192232, 0.954360, 0.000000,
                         6.978198,-1.552600, 6.581902, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_LeftHandThumb2 {
                        FrameTransformMatrix {
                           0.960842, 0.051942,-0.272185, 0.000000,
                          -0.014008, 0.990123, 0.139500, 0.000000,
                           0.276743,-0.130225, 0.952079, 0.000000,
                           3.180302,-1.822098, 2.029397, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_LeftHandThumb3 {
                          FrameTransformMatrix {
                             0.947925, 0.148728,-0.281634, 0.000000,
                            -0.127929, 0.987604, 0.090957, 0.000000,
                             0.291670,-0.050192, 0.955201, 0.000000,
                             3.394405,-1.959701, 1.959799, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_LeftHandThumb4 {
                            FrameTransformMatrix {
                               1.000000, 0.000000,-0.000000, 0.000000,
                              -0.000000, 1.000000,-0.000000, 0.000000,
                              -0.000000, 0.000000, 1.000000, 0.000000,
                               2.907604,-1.725102, 1.817308, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_LeftHandThumb4_end {
                              FrameTransformMatrix {
                                 1.000000,-0.000000, 0.000000, 0.000000,
                                 0.000000, 1.000000,-0.000000, 0.000000,
                                -0.000000, 0.000000, 1.000000, 0.000000,
                                 0.000002, 3.838305, 0.000003, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_LeftHandThumb4_end
                          } // End of ROBOT_SOLDIER_RIG_LeftHandThumb4
                        } // End of ROBOT_SOLDIER_RIG_LeftHandThumb3
                      } // End of ROBOT_SOLDIER_RIG_LeftHandThumb2
                    } // End of ROBOT_SOLDIER_RIG_LeftHandThumb1
                  } // End of ROBOT_SOLDIER_RIG_LeftHand
                } // End of ROBOT_SOLDIER_RIG_LeftForeArm
              } // End of ROBOT_SOLDIER_RIG_LeftArm
            } // End of ROBOT_SOLDIER_RIG_LeftShoulder
            Frame ROBOT_SOLDIER_RIG_Neck {
              FrameTransformMatrix {
                 0.992887,-0.117751,-0.017607, 0.000000,
                 0.118533, 0.963732, 0.239103, 0.000000,
                -0.011186,-0.239489, 0.970835, 0.000000,
                -0.000001, 9.786894, 0.792903, 1.000000;;
              }
              Frame ROBOT_SOLDIER_RIG_Head {
                FrameTransformMatrix {
                   0.933805, 0.189856,-0.303253, 0.000000,
                  -0.279765, 0.915815,-0.288121, 0.000000,
                   0.223023, 0.353889, 0.908308, 0.000000,
                   0.000000, 7.233997,-1.138403, 1.000000;;
                }
                Frame ROBOT_SOLDIER_RIG_HeadTop_End {
                  FrameTransformMatrix {
                     1.000000, 0.000001,-0.000000, 0.000000,
                    -0.000001, 1.000000, 0.000001, 0.000000,
                    -0.000000,-0.000001, 1.000000, 0.000000,
                     0.000203,30.054060, 4.110004, 1.000000;;
                  }
                  Frame ROBOT_SOLDIER_RIG_HeadTop_End_end {
                    FrameTransformMatrix {
                       1.000000,-0.000000, 0.000000, 0.000000,
                       0.000000, 1.000000,-0.000000, 0.000000,
                      -0.000000, 0.000000, 1.000000, 0.000000,
                       0.000005,30.333670, 0.000000, 1.000000;;
                    }
                  } // End of ROBOT_SOLDIER_RIG_HeadTop_End_end
                } // End of ROBOT_SOLDIER_RIG_HeadTop_End
              } // End of ROBOT_SOLDIER_RIG_Head
            } // End of ROBOT_SOLDIER_RIG_Neck
            Frame ROBOT_SOLDIER_RIG_RightShoulder {
              FrameTransformMatrix {
                 0.819112,-0.514744,-0.253168, 0.000000,
                 0.542268, 0.838771, 0.049083, 0.000000,
                 0.187085,-0.177490, 0.966176, 0.000000,
                -21.496603, 2.870693, 0.705595, 1.000000;;
              }
              Frame ROBOT_SOLDIER_RIG_RightArm {
                FrameTransformMatrix {
                   0.101077, 0.949203,-0.297988, 0.000000,
                  -0.716264, 0.277305, 0.640365, 0.000000,
                   0.690470, 0.148712, 0.707909, 0.000000,
                  -12.978001, 0.690008,-1.526506, 1.000000;;
                }
                Frame ROBOT_SOLDIER_RIG_RightForeArm {
                  FrameTransformMatrix {
                     0.958791,-0.078519,-0.273048, 0.000000,
                     0.052456, 0.993453,-0.101486, 0.000000,
                     0.279229, 0.082981, 0.956632, 0.000000,
                    -31.225100,-0.028013, 0.000004, 1.000000;;
                  }
                  Frame ROBOT_SOLDIER_RIG_RightHand {
                    FrameTransformMatrix {
                       0.277260,-0.676346, 0.682410, 0.000000,
                       0.960403, 0.215380,-0.176741, 0.000000,
                      -0.027440, 0.704392, 0.709281, 0.000000,
                      -31.363314, 0.000002, 0.000005, 1.000000;;
                    }
                    Frame ROBOT_SOLDIER_RIG_RightHandIndex1 {
                      FrameTransformMatrix {
                         0.977773, 0.030374,-0.207453, 0.000000,
                        -0.027357, 0.999474, 0.017398, 0.000000,
                         0.207872,-0.011335, 0.978090, 0.000000,
                        -13.672999, 0.151998, 4.666803, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_RightHandIndex2 {
                        FrameTransformMatrix {
                           0.966918, 0.254672,-0.014544, 0.000000,
                          -0.255004, 0.966482,-0.029737, 0.000000,
                           0.006483, 0.032462, 0.999452, 0.000000,
                          -5.537994, 0.000001, 0.000003, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_RightHandIndex3 {
                          FrameTransformMatrix {
                             0.969564, 0.244741,-0.006872, 0.000000,
                            -0.244740, 0.969588, 0.000941, 0.000000,
                             0.006893, 0.000770, 0.999976, 0.000000,
                            -4.575006,-0.000002, 0.000001, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_RightHandIndex4 {
                            FrameTransformMatrix {
                               1.000000,-0.000000, 0.000000, 0.000000,
                               0.000000, 1.000000, 0.000000, 0.000000,
                              -0.000000,-0.000000, 1.000000, 0.000000,
                              -4.103006,-0.000001, 0.000002, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_RightHandIndex4_end {
                              FrameTransformMatrix {
                                 1.000000, 0.000000, 0.000000, 0.000000,
                                -0.000000, 1.000000, 0.000000, 0.000000,
                                -0.000000,-0.000000, 1.000000, 0.000000,
                                 0.000001, 4.102996, 0.000001, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_RightHandIndex4_end
                          } // End of ROBOT_SOLDIER_RIG_RightHandIndex4
                        } // End of ROBOT_SOLDIER_RIG_RightHandIndex3
                      } // End of ROBOT_SOLDIER_RIG_RightHandIndex2
                    } // End of ROBOT_SOLDIER_RIG_RightHandIndex1
                    Frame ROBOT_SOLDIER_RIG_RightHandMiddle1 {
                      FrameTransformMatrix {
                         0.995942,-0.045924,-0.077396, 0.000000,
                         0.050837, 0.996734, 0.062750, 0.000000,
                         0.074261,-0.066430, 0.995024, 0.000000,
                        -13.846001, 0.130998, 1.509804, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_RightHandMiddle2 {
                        FrameTransformMatrix {
                           0.927576, 0.372338,-0.031097, 0.000000,
                          -0.371604, 0.910668,-0.180542, 0.000000,
                          -0.038903, 0.179022, 0.983076, 0.000000,
                          -6.631997,-0.000001, 0.000002, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_RightHandMiddle3 {
                          FrameTransformMatrix {
                             0.966147, 0.256978, 0.022852, 0.000000,
                            -0.256982, 0.966412,-0.002834, 0.000000,
                            -0.022812,-0.003135, 0.999735, 0.000000,
                            -4.461000,-0.000001,-0.000003, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_RightHandMiddle4 {
                            FrameTransformMatrix {
                               1.000000, 0.000000, 0.000000, 0.000000,
                              -0.000000, 1.000000, 0.000000, 0.000000,
                               0.000000,-0.000000, 1.000000, 0.000000,
                              -4.718001,-0.000006,-0.000000, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_RightHandMiddle4_end {
                              FrameTransformMatrix {
                                 1.000000,-0.000000, 0.000000, 0.000000,
                                 0.000000, 1.000000, 0.000000, 0.000000,
                                 0.000000,-0.000000, 1.000000, 0.000000,
                                -0.000008, 4.718000, 0.000003, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_RightHandMiddle4_end
                          } // End of ROBOT_SOLDIER_RIG_RightHandMiddle4
                        } // End of ROBOT_SOLDIER_RIG_RightHandMiddle3
                      } // End of ROBOT_SOLDIER_RIG_RightHandMiddle2
                    } // End of ROBOT_SOLDIER_RIG_RightHandMiddle1
                    Frame ROBOT_SOLDIER_RIG_RightHandPinky1 {
                      FrameTransformMatrix {
                         0.999021,-0.003714,-0.044080, 0.000000,
                        -0.009623, 0.954356,-0.298518, 0.000000,
                         0.043177, 0.298650, 0.953386, 0.000000,
                        -13.951005,-0.226010,-4.916297, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_RightHandPinky2 {
                        FrameTransformMatrix {
                           0.935196, 0.342383, 0.090458, 0.000000,
                          -0.351866, 0.927232, 0.128185, 0.000000,
                          -0.039987,-0.151707, 0.987616, 0.000000,
                          -4.251002,-0.000000, 0.000006, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_RightHandPinky3 {
                          FrameTransformMatrix {
                             0.921635, 0.385576, 0.043826, 0.000000,
                            -0.385579, 0.922634,-0.008728, 0.000000,
                            -0.043801,-0.008855, 0.999001, 0.000000,
                            -2.820999,-0.000001, 0.000000, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_RightHandPinky4 {
                            FrameTransformMatrix {
                               1.000000,-0.000000,-0.000000, 0.000000,
                               0.000000, 1.000000,-0.000000, 0.000000,
                               0.000000, 0.000000, 1.000000, 0.000000,
                              -3.367002,-0.000006,-0.000002, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_RightHandPinky4_end {
                              FrameTransformMatrix {
                                 1.000000, 0.000000, 0.000000, 0.000000,
                                -0.000000, 1.000000, 0.000000, 0.000000,
                                 0.000000,-0.000000, 1.000000, 0.000000,
                                -0.000000, 3.366998, 0.000006, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_RightHandPinky4_end
                          } // End of ROBOT_SOLDIER_RIG_RightHandPinky4
                        } // End of ROBOT_SOLDIER_RIG_RightHandPinky3
                      } // End of ROBOT_SOLDIER_RIG_RightHandPinky2
                    } // End of ROBOT_SOLDIER_RIG_RightHandPinky1
                    Frame ROBOT_SOLDIER_RIG_RightHandRing1 {
                      FrameTransformMatrix {
                         0.997869,-0.064813,-0.007555, 0.000000,
                         0.060464, 0.961962,-0.266408, 0.000000,
                         0.024534, 0.265383, 0.963831, 0.000000,
                        -14.373003, 0.009998,-1.886897, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_RightHandRing2 {
                        FrameTransformMatrix {
                           0.926760, 0.366101, 0.084176, 0.000000,
                          -0.372221, 0.925163, 0.074325, 0.000000,
                          -0.050666,-0.100214, 0.993675, 0.000000,
                          -5.068993,-0.000003, 0.000001, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_RightHandRing3 {
                          FrameTransformMatrix {
                             0.932364, 0.357635, 0.052861, 0.000000,
                            -0.357629, 0.933811,-0.009897, 0.000000,
                            -0.052902,-0.009677, 0.998553, 0.000000,
                            -3.782003, 0.000000, 0.000008, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_RightHandRing4 {
                            FrameTransformMatrix {
                               1.000000, 0.000000,-0.000000, 0.000000,
                               0.000000, 1.000000, 0.000000, 0.000000,
                               0.000000,-0.000000, 1.000000, 0.000000,
                              -3.803996, 0.000001, 0.000003, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_RightHandRing4_end {
                              FrameTransformMatrix {
                                 1.000000,-0.000000,-0.000000, 0.000000,
                                 0.000000, 1.000000,-0.000000, 0.000000,
                                 0.000000, 0.000000, 1.000000, 0.000000,
                                -0.000003, 3.804008,-0.000000, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_RightHandRing4_end
                          } // End of ROBOT_SOLDIER_RIG_RightHandRing4
                        } // End of ROBOT_SOLDIER_RIG_RightHandRing3
                      } // End of ROBOT_SOLDIER_RIG_RightHandRing2
                    } // End of ROBOT_SOLDIER_RIG_RightHandRing1
                    Frame ROBOT_SOLDIER_RIG_RightHandThumb1 {
                      FrameTransformMatrix {
                         0.917752,-0.392189,-0.062602, 0.000000,
                         0.378849, 0.911810,-0.158352, 0.000000,
                         0.119185, 0.121611, 0.985396, 0.000000,
                        -6.977999,-1.552004, 6.581906, 1.000000;;
                      }
                      Frame ROBOT_SOLDIER_RIG_RightHandThumb2 {
                        FrameTransformMatrix {
                           0.991079,-0.132858, 0.010535, 0.000000,
                           0.117865, 0.910637, 0.396041, 0.000000,
                          -0.062210,-0.391266, 0.918173, 0.000000,
                          -3.179994,-1.823002, 2.029400, 1.000000;;
                        }
                        Frame ROBOT_SOLDIER_RIG_RightHandThumb3 {
                          FrameTransformMatrix {
                             0.996851,-0.068424, 0.040085, 0.000000,
                             0.069190, 0.997440,-0.018058, 0.000000,
                            -0.038747, 0.020774, 0.999033, 0.000000,
                            -3.395007,-1.958997, 1.959803, 1.000000;;
                          }
                          Frame ROBOT_SOLDIER_RIG_RightHandThumb4 {
                            FrameTransformMatrix {
                               1.000000, 0.000001,-0.000000, 0.000000,
                              -0.000001, 1.000000,-0.000001, 0.000000,
                               0.000000, 0.000001, 1.000000, 0.000000,
                              -2.906997,-1.725001, 1.817402, 1.000000;;
                            }
                            Frame ROBOT_SOLDIER_RIG_RightHandThumb4_end {
                              FrameTransformMatrix {
                                 1.000000, 0.000000,-0.000000, 0.000000,
                                -0.000000, 1.000000, 0.000001, 0.000000,
                                 0.000000,-0.000001, 1.000000, 0.000000,
                                 0.000003, 3.837807,-0.000002, 1.000000;;
                              }
                            } // End of ROBOT_SOLDIER_RIG_RightHandThumb4_end
                          } // End of ROBOT_SOLDIER_RIG_RightHandThumb4
                        } // End of ROBOT_SOLDIER_RIG_RightHandThumb3
                      } // End of ROBOT_SOLDIER_RIG_RightHandThumb2
                    } // End of ROBOT_SOLDIER_RIG_RightHandThumb1
                  } // End of ROBOT_SOLDIER_RIG_RightHand
                } // End of ROBOT_SOLDIER_RIG_RightForeArm
              } // End of ROBOT_SOLDIER_RIG_RightArm
            } // End of ROBOT_SOLDIER_RIG_RightShoulder
          } // End of ROBOT_SOLDIER_RIG_Spine2
        } // End of ROBOT_SOLDIER_RIG_Spine1
      } // End of ROBOT_SOLDIER_RIG_Spine
    } // End of ROBOT_SOLDIER_RIG_Hips
  } // End of ROBOT_SOLDIER_RIG
} // End of Root
AnimationSet Global {
  Animation {
    {ROBOT_SOLDIER_RIG}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.707107, 0.707107, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 0.100000, 0.100000, 0.100000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000000, 0.000000, 0.000000;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_Hips}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.920623,-0.337526,-0.196059, 0.009506;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 3.508505,17.198601,-1.709373;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_Spine}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.966728, 0.243992, 0.011793,-0.075928;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000000,13.395802,-1.227298;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_Spine1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.988566, 0.146767,-0.029058, 0.018750;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000100,13.655706,-1.422300;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_Spine2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.988359, 0.147571,-0.026509, 0.025811;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000100,13.360202,-1.626499;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_Neck}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.990890, 0.120748, 0.001620,-0.059614;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000001, 9.786894, 0.792903;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_Head}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.969269,-0.165591, 0.135740, 0.121128;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000000, 7.233997,-1.138403;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_HeadTop_End}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000203,30.054060, 4.110004;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_HeadTop_End_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000005,30.333670, 0.000000;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftShoulder}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.910319, 0.047302,-0.167875, 0.375365;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;21.496601, 2.870901, 0.705600;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftArm}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.376807, 0.240180,-0.575152,-0.685223;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;12.978003, 0.690194,-1.526495;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftForeArm}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.863400,-0.490757,-0.042991, 0.108859;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;31.225210,-0.028202, 0.000004;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHand}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.499980,-0.660525, 0.476921, 0.293723;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;31.363201,-0.000007, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandMiddle1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.998334,-0.039684,-0.029415,-0.029832;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;13.845897, 0.130694, 1.509796;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandMiddle2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.987858,-0.020660, 0.008975,-0.153715;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 6.632604, 0.000001, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandMiddle3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.996638, 0.000169, 0.005049,-0.081772;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 4.460296,-0.000001, 0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandMiddle4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000,-0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 4.718607,-0.000000, 0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandMiddle4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000006, 4.718601, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandThumb1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.980774,-0.110918,-0.102553, 0.123542;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 6.978198,-1.552600, 6.581902;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandThumb2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.987806, 0.068264, 0.138926, 0.016691;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 3.180302,-1.822098, 2.029397;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandThumb3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.986247, 0.035779, 0.145325, 0.070129;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 3.394405,-1.959701, 1.959799;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandThumb4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000,-0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 2.907604,-1.725102, 1.817308;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandThumb4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000002, 3.838305, 0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandIndex1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.994023, 0.045663,-0.087392,-0.046862;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;13.672699, 0.151797, 4.666800;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandIndex2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.987818,-0.079586,-0.002682,-0.133699;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 5.537905, 0.000001, 0.000004;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandIndex3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.994280, 0.000121, 0.006226,-0.106621;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 4.575105,-0.000000,-0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandIndex4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 4.103002,-0.000001,-0.000004;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandIndex4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000,-0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000001, 4.103001,-0.000000;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandRing1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.990196,-0.139315, 0.010148, 0.000687;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;14.372702, 0.009896,-1.887006;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandRing2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.984575, 0.022628, 0.031011,-0.170700;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 5.069504, 0.000000,-0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandRing3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.995402,-0.000054, 0.017437,-0.094185;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 3.781899,-0.000000,-0.000006;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandRing4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 3.804002,-0.000001,-0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandRing4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000001, 3.804002,-0.000004;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandPinky1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.973385,-0.227125,-0.002591,-0.030485;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;13.950800,-0.226408,-4.916303;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandPinky2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.985256, 0.056779, 0.050249,-0.153368;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 4.250996, 0.000001, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandPinky3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.998909, 0.000007, 0.012267,-0.045066;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 2.821101, 0.000001,-0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandPinky4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 3.367102, 0.000002, 0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftHandPinky4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000003, 3.367099, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightShoulder}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.951848, 0.059509, 0.115631,-0.277621;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-21.496603, 2.870693, 0.705595;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightArm}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.722200, 0.170193, 0.342169, 0.576526;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-12.978001, 0.690008,-1.526506;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightForeArm}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.988544,-0.046651, 0.139669,-0.033123;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-31.225100,-0.028013, 0.000004;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHand}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.741944,-0.296900,-0.239186,-0.551507;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-31.363314, 0.000002, 0.000005;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandMiddle1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.998461, 0.032345, 0.037973,-0.024228;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-13.846001, 0.130998, 1.509804;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandMiddle2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.977410,-0.091969,-0.001997, 0.190284;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-6.631997,-0.000001, 0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandMiddle3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.991501, 0.000076,-0.011514, 0.129591;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-4.461000,-0.000001,-0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandMiddle4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-4.718001,-0.000006,-0.000000;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandMiddle4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000008, 4.718000, 0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandThumb1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.976596,-0.071668, 0.046536,-0.197379;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-6.977999,-1.552004, 6.581906;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandThumb2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.977227, 0.201414,-0.018610,-0.064141;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-3.179994,-1.823002, 2.029400;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandThumb3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.999165,-0.009716,-0.019725,-0.034432;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-3.395007,-1.958997, 1.959803;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandThumb4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000, 0.000000, 0.000001;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-2.906997,-1.725001, 1.817402;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandThumb4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000003, 3.837807,-0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandIndex1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.994402, 0.007224, 0.104416, 0.014514;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-13.672999, 0.151998, 4.666803;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandIndex2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.991571,-0.015682, 0.005302, 0.128502;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-5.537994, 0.000001, 0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandIndex3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.992362, 0.000043, 0.003468, 0.123312;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-4.575006,-0.000002, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandIndex4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-4.103006,-0.000001, 0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandIndex4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000,-0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000001, 4.102996, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandRing1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.990412,-0.134235, 0.008100,-0.031623;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-14.373003, 0.009998,-1.886897;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandRing2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.980510, 0.044502,-0.034381, 0.188249;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-5.068993,-0.000003, 0.000001;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandRing3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.982946,-0.000056,-0.026899, 0.181919;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-3.782003, 0.000000, 0.000008;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandRing4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-3.803996, 0.000001, 0.000003;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandRing4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000, 0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000003, 3.804008,-0.000000;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandPinky1}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.988277,-0.151063, 0.022073, 0.001495;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-13.951005,-0.226010,-4.916297;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandPinky2}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.981076, 0.071323,-0.033240, 0.176910;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-4.251002,-0.000000, 0.000006;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandPinky3}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.980213, 0.000032,-0.022349, 0.196680;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-2.820999,-0.000001, 0.000000;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandPinky4}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000,-0.000000, 0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-3.367002,-0.000006,-0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightHandPinky4_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000000, 3.366998, 0.000006;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftUpLeg}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.580374,-0.722461, 0.128989, 0.352956;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;12.894799,-9.482498,-0.055401;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftLeg}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.614990, 0.786999, 0.025824,-0.041873;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.244693,-40.595406,-0.516993;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftFoot}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.969804, 0.212534,-0.118693, 0.014909;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.244698,-42.048004,-2.057602;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftToeBase}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.994711,-0.101736, 0.001419, 0.014103;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.373402,-10.492208,12.640696;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftToe_End}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000,-0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000002,-0.000004, 9.992504;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_LeftToe_End_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000,-0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000004, 9.992497,-0.000002;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightUpLeg}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.696591,-0.709535,-0.019895, 0.104524;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-12.894800,-9.482503,-0.055399;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightLeg}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.748797, 0.654084,-0.090856,-0.056763;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.244694,-40.595402,-0.516990;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightFoot}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.951732,-0.300965,-0.005440, 0.059974;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.244700,-42.048012,-2.057609;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightToeBase}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-0.999987, 0.003922,-0.001665, 0.002672;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.373398,-10.492219,12.640696;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightToe_End}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3; 0.000000,-0.000001, 9.992503;;;
    }
  }
  Animation {
    {ROBOT_SOLDIER_RIG_RightToe_End_end}
    AnimationKey { // Rotation
      0;
      1;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      1;
      0;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      1;
      0;3;-0.000002, 9.992506,-0.000002;;;
    }
  }
} // End of AnimationSet Global
