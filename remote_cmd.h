/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REMOTE_CMD_H_RPCGEN
#define _REMOTE_CMD_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct ClientInput {
	char *program_name_;
	char *flags_;
	char *stdin_;
	int part_;
	int parts_;
};
typedef struct ClientInput ClientInput;

struct ServerOutput {
	char *stdout_;
	char *stderr_;
	int status_;
	int part_;
	int parts_;
};
typedef struct ServerOutput ServerOutput;

#define remote_cmd 0x20000000
#define remote_cmd_ver 1

#if defined(__STDC__) || defined(__cplusplus)
#define execute_cmd 1
extern  ServerOutput * execute_cmd_1(ClientInput *, CLIENT *);
extern  ServerOutput * execute_cmd_1_svc(ClientInput *, struct svc_req *);
extern int remote_cmd_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define execute_cmd 1
extern  ServerOutput * execute_cmd_1();
extern  ServerOutput * execute_cmd_1_svc();
extern int remote_cmd_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_ClientInput (XDR *, ClientInput*);
extern  bool_t xdr_ServerOutput (XDR *, ServerOutput*);

#else /* K&R C */
extern bool_t xdr_ClientInput ();
extern bool_t xdr_ServerOutput ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REMOTE_CMD_H_RPCGEN */
