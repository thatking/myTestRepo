

SRCDIR += rear_view_panorama

SRCS_REAR_VIEW_PANORAMA_IMAGETRANSFORM = imageTransformLink_algPlugin.c  \

SRCS_REAR_VIEW_PANORAMA_SEAMDETECTION = seamDetectionLink_algPlugin.c \

SRCS_REAR_VIEW_PANORAMA_STITCHING = stitchingLink_algPlugin.c \

SRCS_c66xdsp_1 +=  $(SRCS_REAR_VIEW_PANORAMA_STITCHING) $(SRCS_REAR_VIEW_PANORAMA_IMAGETRANSFORM) $(SRCS_REAR_VIEW_PANORAMA_SEAMDETECTION)
SRCS_c66xdsp_2 +=  $(SRCS_REAR_VIEW_PANORAMA_STITCHING) $(SRCS_REAR_VIEW_PANORAMA_IMAGETRANSFORM) $(SRCS_REAR_VIEW_PANORAMA_SEAMDETECTION)





