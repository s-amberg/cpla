#ifndef WIZARD_H_
#define WIZARD_H_
#if defined(_WIN32)
#define WIZARD_EXPORT_DLL __declspec(dllexport)
#else
#define WIZARD_EXPORT_DLL [[gnu::visibility("default")]]
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wizard *wizard;
typedef struct Wizard const *cwizard;
typedef struct Error *error;

WIZARD_EXPORT_DLL char const *error_message(error error);
WIZARD_EXPORT_DLL void error_dispose(error error);

WIZARD_EXPORT_DLL wizard create_wizard(char const *name, error *out_error);
WIZARD_EXPORT_DLL void dispose_wizard(wizard toDispose);

WIZARD_EXPORT_DLL char const *do_magic(wizard w, char const *wish, error *out_error);
WIZARD_EXPORT_DLL void learn_spell(wizard w, char const *spell);
WIZARD_EXPORT_DLL void mix_and_store_potion(wizard w, char const *potion);
WIZARD_EXPORT_DLL char const *wizard_name(cwizard w);

#ifdef __cplusplus
}
#endif
#endif /* WIZARD_H_ */
