# RageFaceBlocker

This application is split into 3 sections:

1) The C++ detection program using OpenCV, both an offline processing step and online step.
2) The server application which uses the online step of the C++ detection program in a Rails Application through a JSON interface.
3) The chrome extension which communicates with the Rails Application to filter out the images on the facebook wall.