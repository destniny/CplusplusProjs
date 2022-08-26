/*
 * Empty C++ Application
 */
#include <stdio.h>
#include "xaxidma.h"
#include "xc1.h"

///// first convolution layer /////
#define c1_input_width 4
#define c1_filter 6
///// 2D kernel 5*5			  /////
#define c1_filter_size 2
///// 3D output 28*28*6       /////
#define c1_output_size 3
#define c1_output_width 6

#define mem_base_addr 0x01000000
#define tx_buffer_base (mem_base_addr + 0x00100000)
#define rx_buffer_base (mem_base_addr + 0x00300000)

float *m_dma_buffer_RX = (float*)rx_buffer_base;
float input[c1_input_width][c1_input_width]={{0,1,1,1},
				 {1,0,1,1},
				 {1,1,0,1},
				 {1,1,1,0}};

float weight[c1_filter*c1_filter_size*c1_filter_size]={-1,1,1,1,
														1,-1,1,1,
														1,1,-1,1,
														1,1,1,-1,
														-1,1,1,1,
														1,-1,1,1};
float bias[c1_filter]={2,2,2,2,2,2};


XAxiDma axiDma;
int initDMA()
{
	XAxiDma_Config *CfgPtr;
	CfgPtr = XAxiDma_LookupConfig(XPAR_AXI_DMA_0_DEVICE_ID);
	XAxiDma_CfgInitialize(&axiDma,CfgPtr);

	// Disable interrupts
	XAxiDma_IntrDisable(&axiDma,XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&axiDma,XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DMA_TO_DEVICE);

	return XST_SUCCESS;
}


XC1 doCnn;
int initC1()
{
	int status;

	XC1_Config *doCnn_cfg;
	doCnn_cfg = XC1_LookupConfig(XPAR_C1_0_DEVICE_ID);
	if (!doCnn_cfg)
	{
		printf("Error loading config for doHist_cfg\n");
	}
	status = XC1_CfgInitialize(&doCnn,doCnn_cfg);
	if (status != XST_SUCCESS)
	{
		printf("Error initializing for doHist\n");
	}

	return status;
}
int main()
{
	initDMA();
	initC1();
	printf("Starting.... HW\n");
	 XC1_Write_filter_w_Words(&doCnn, 0, (int*)weight, 24);
	 XC1_Write_filter_b_Words(&doCnn, 0, (int*)bias, 6);
	 XC1_Start(&doCnn);



	 Xil_DCacheFlushRange((u32)input,c1_input_width*c1_input_width*sizeof(int));
	 Xil_DCacheFlushRange((u32)m_dma_buffer_RX,c1_output_size*c1_output_width*c1_output_width*sizeof(int));

	 XAxiDma_SimpleTransfer(&axiDma,(u32)input,c1_input_width*c1_input_width*sizeof(int),XAXIDMA_DMA_TO_DEVICE);
	 XAxiDma_SimpleTransfer(&axiDma,(u32)m_dma_buffer_RX,c1_output_size*c1_output_width*c1_output_width*sizeof(float),XAXIDMA_DEVICE_TO_DMA);

	 while(XAxiDma_Busy(&axiDma,XAXIDMA_DMA_TO_DEVICE));
	 while(XAxiDma_Busy(&axiDma,XAXIDMA_DEVICE_TO_DMA));

	 Xil_DCacheInvalidateRange((u32)m_dma_buffer_RX,c1_output_size*c1_output_width*c1_output_width*sizeof(int));

	 for(int z = 0; z < c1_output_width;z++){
	 		printf("%d's feature\n",z);
	 		for(int i = 0; i < c1_output_size; i++){
	 			printf("|");
	 			for(int j = 0; j < c1_output_size; j++){
	 				printf("%f|",m_dma_buffer_RX[z*c1_output_size*c1_output_size+i*c1_output_size+j]);
	 			}
	 			printf("\n");
	 		}
	 		printf("\n\n");
	 	}
	return 0;
}
