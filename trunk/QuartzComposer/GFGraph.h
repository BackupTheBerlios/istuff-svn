/* 
 *     Created by Clockskew.  Use for whatever.  Don't sue me. 
 */


#import "GFNode.h"

@class GFList;

@interface GFGraph : GFNode 
{
    GFList *_nodes;
    GFList *_connections;
    BOOL _finalizing;
    void *_unused2[4];
}

- (void)_finalize_GFGraph;
- (void)finalize;
- (void)dealloc;
- (BOOL)canAddNode:(id)fp8;
- (BOOL)addNode:(id)fp8 forKey:(id)fp12;
- (BOOL)addNode:(id)fp8;
- (void)removeNodeForKey:(id)fp8;
- (void)removeNode:(id)fp8;
- (id)nodes;
- (BOOL)canConnectPort:(id)fp8 toPort:(id)fp12;
- (id)argumentsForConnectionFromPort:(id)fp8 toPort:(id)fp12;
- (id)createConnectionFromPort:(id)fp8 toPort:(id)fp12 forKey:(id)fp16;
- (id)connectPort:(id)fp8 toPort:(id)fp12;
- (void)deleteConnectionForKey:(id)fp8;
- (void)breakConnection:(id)fp8;
- (id)connections;
- (id)nodeForKey:(id)fp8;
- (id)keyForNode:(id)fp8;
- (id)connectionForKey:(id)fp8;
- (id)keyForConnection:(id)fp8;
- (id)pathForNode:(id)fp8;
- (id)nodeForPath:(id)fp8;
- (id)pathForPort:(id)fp8;
- (id)portForPath:(id)fp8;
- (BOOL)canPublishPort:(id)fp8;
- (id)createProxyPortWithOriginalPort:(id)fp8 forKey:(id)fp12;
- (id)publishPort:(id)fp8;
- (void)deleteProxyPortForKey:(id)fp8;
- (void)unpublishPort:(id)fp8;
- (id)proxyPortForOriginalPort:(id)fp8;
- (id)isPortPublished:(id)fp8;
- (id)state;
- (BOOL)setState:(id)fp8;

@end

