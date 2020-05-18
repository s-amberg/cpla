#ifndef WIZARD_H_
#define WIZARD_H_
#if defined(_WIN32)
#define WIZARD_EXPORT_DLL __declspec(dllexport)
#else
//assumes -fvisibility=hidden
#define WIZARD_EXPORT_DLL __attribute__ ((visibility ("default")))
#endif
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wizard * wizard;
typedef struct Wizard const * cwizard;
typedef struct Error * error;

WIZARD_EXPORT_DLL
char const *error_message(error error);
WIZARD_EXPORT_DLL
void error_dispose(error error);

WIZARD_EXPORT_DLL
wizard createWizard(char const *name, error *out_error);
WIZARD_EXPORT_DLL
void disposeWizard(wizard toDispose);

WIZARD_EXPORT_DLL
char const *doMagic(wizard w, char const *wish, error *out_error);
WIZARD_EXPORT_DLL
void learnSpell(wizard w, char const *spell);
WIZARD_EXPORT_DLL
void mixAndStorePotion(wizard w, char const *potion);
WIZARD_EXPORT_DLL
char const *wizardName(cwizard w);

#ifdef __cplusplus
}
#endif
#endif /* WIZARD_H_ */
