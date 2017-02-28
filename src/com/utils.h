#ifndef __UTILS_H__
#define __UTILS_H__

#define SAFE_DEL(p) do { if (p != NULL) delete p; p = NULL; } while (0)
#define SAFE_DEL_ARRAY(p) do { if (p != NULL) delete[] p; p = NULL; } while (0)

#endif