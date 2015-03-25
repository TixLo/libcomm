#ifndef __COMM_MACROS_H__
#define __COMM_MACROS_H__

#define COMM_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){ varName = var; }

#define COMM_SYNTHESIZE_RDONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\

#define COMM_SYNTHESIZE_WRONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual void Set##funName(varType var){ varName = var; }

#endif//__COMM_MACROS_H__