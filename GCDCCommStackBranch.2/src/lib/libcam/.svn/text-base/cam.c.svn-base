/*
 * $Id: cam.c $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <inttypes.h>

#include <calm/calmmedia/mininl.h>
#include <linux/calm.h>

#include "CooperativeAwarenessMessage.h"

#include "cam.h"

CooperativeAwarenessMessage_t	*getDefaultCam(long nodeid, camtype nodetype)
{
	CooperativeAwarenessMessage_t	*cam;

	cam = calloc(1, sizeof(CooperativeAwarenessMessage_t));
	if (cam != NULL) {
		cam->header.nodeID = nodeid;
		if (nodetype == CAM_VEHICLE) {
			cam->payload.present = CamPayload_PR_vehicleCamPayload;
		}
		if (nodetype == CAM_RSU) {
			cam->payload.present = CamPayload_PR_rsuCamPayload;
			cam->payload.choice.rsuCamPayload.weather = Weather_unknown;
		}
	}

	return cam;
}

int encodeCam(CooperativeAwarenessMessage_t *cam, unsigned char *buffer, int buflen)
{
	asn_enc_rval_t	ec;      /* Encoder return value  */
	int		result = 0;

	int write_out(const void *encdata, size_t size, void *app_key)
	{
		if (size > buflen) return -1;

		memcpy(buffer, encdata, size);
		buffer += size;
		buflen -= size;
		result += size;
		return 0;
	}

	ec = der_encode(&asn_DEF_CooperativeAwarenessMessage, cam, write_out, 0);
	if (ec.encoded == -1) {
		fprintf(stderr, "Could not encode CAM (at %s)\n",
			  ec.failed_type ? ec.failed_type->name : "unknown");
		result = -1;
	}
	return result;
}

#ifdef LIBCAM_TEST

int main(int argc, char *argv[])
{
	int result;
	unsigned char buffer[1024];
	int	cnt;
	char errbuf[128];  /* Buffer for error message */
	size_t errlen = sizeof(errbuf);  /* Size of the buffer */

	CooperativeAwarenessMessage_t	*cam = getDefaultCam(767, CAM_RSU);

	result = asn_check_constraints(&asn_DEF_CooperativeAwarenessMessage, cam, errbuf, &errlen);
	if (result) {
		fprintf(stderr, "Constraint validation failed: %s\n", errbuf);
		exit(1);
	} else {
		printf("Constrainst checked OK\n");
	}

	asn_fprint(stdout, &asn_DEF_CooperativeAwarenessMessage, cam);

	result = encodeCam(cam, buffer, sizeof(buffer));

	printf("Encode result = %d\n", result);

	printf("Buffer dump:\n");
	for (cnt = 0; cnt < result; cnt++) {
		printf("%d, ", buffer[cnt]);
	}
	printf("\b\n");
	
	exit(0);
}

#endif
