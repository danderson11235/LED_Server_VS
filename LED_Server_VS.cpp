#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <ctime>
#include <kiss_fftr.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000
#define SERVER "192.168.1.129"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 4210	//The port on which to listen for incoming data

const int nfft = 1024;
const float freq = 31250;
const float peri = 1 / freq;
const float c_peri = 1000000 * peri;
void getAudio();

//Audio
const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);


int main(void)
{
	//UDP
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char message[BUFLEN];
	WSADATA wsa;
	/*
	//fft
	kiss_fftr_cfg cfg = kiss_fftr_alloc(nfft, 0, 0, 0);
	float in[nfft];
	kiss_fft_cpx out[nfft];

	//Capture
	HRESULT hr;
	REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
	REFERENCE_TIME hnsActualDuration;
	UINT32 bufferFrameCount;
	UINT32 numFramesAvailable;
	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioClient* pAudioClient = NULL;
	IAudioCaptureClient* pCaptureClient = NULL;
	WAVEFORMATEX* pwfx = NULL;
	UINT32 packetLength = 0;
	BOOL bDone = FALSE;
	BYTE* pData;
	DWORD flags;

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		(void**)&pEnumerator);

	hr = pEnumerator->GetDefaultAudioEndpoint(
		eCapture, eConsole, &pDevice);

	hr = pDevice->Activate(
		IID_IAudioClient, CLSCTX_ALL,
		NULL, (void**)&pAudioClient);

	hr = pAudioClient->GetMixFormat(&pwfx);

	hr = pAudioClient->Initialize(
		AUDCLNT_SHAREMODE_SHARED,
		0,
		hnsRequestedDuration,
		0,
		pwfx,
		NULL);

	// Get the size of the allocated buffer.
	hr = pAudioClient->GetBufferSize(&bufferFrameCount);

	hr = pAudioClient->GetService(
		IID_IAudioCaptureClient,
		(void**)&pCaptureClient);

	// Calculate the actual duration of the allocated buffer.
	hnsActualDuration = (double)REFTIMES_PER_SEC *
	bufferFrameCount / pwfx->nSamplesPerSec;

	hr = pAudioClient->Start();  // Start recording.
	*/
	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
	clock_t c_count_old = clock();
	clock_t c_count_new = clock();
	//float* audio[nfft];
	message[0] = (unsigned char)0;
	message[1] = (unsigned char)0;

	//send the message
	if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	closesocket(s);
	WSACleanup();

	//kiss_fftr_free(cfg);
	return 0;
}

void getAudio() {

}
