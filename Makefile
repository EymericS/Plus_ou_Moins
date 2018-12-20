# ##### Self-made function ##### #
# replace in file firth arg all occurence of second arg by third arg and put the result in the fourth arg
# use : $(call replace src_file_path,from,to,out_file_path)
define replace
	ifeq($(OS), Windows_NT)
		powershell -command (get-content $(1)).replace('$(2)', '$(3)') > $(4)
	else
		sed 
endef

BIN_DIR_ALL = bin
OBJ_DIR_ALL = obj
DEP_DIR_ALL = dep

ifeq ($(OS), Windows_NT) # Détecte Windows comme OS pour W10, W8, W7, WXP, W_NT
	RM_FILE ?= del /f /s /q
	RM_DIR ?= rmdir /Q /S
	SLASH ?= $\\
	BIN_DIR = $(BIN_DIR_ALL)$(SLASH)Windows$(SLASH)
	OBJ_DIR = $(OBJ_DIR_ALL)$(SLASH)Windows$(SLASH)
	DEP_DIR = $(DEP_DIR_ALL)$(SLASH)Windows$(SLASH)
else
	RM_FILE ?= rm -f
	RM_DIR ?= rm -rf
	SLASH ?= /
	BIN_DIR = $(BIN_DIR_ALL)$(SLASH)Linux$(SLASH)
	OBJ_DIR = $(OBJ_DIR_ALL)$(SLASH)Linux$(SLASH)
	DEP_DIR = $(DEP_DIR_ALL)$(SLASH)Linux$(SLASH)
endif

CC = gcc # Compilateur utilisé
LD = gcc # Compilateur de lien utilisé
CFLAGS = -g -Wall -Wextra -pedantic -pedantic-errors # Options pour le compilateur
LDFLAGS = # Option pour le compilateur de lien
DEPFLAGS = -MM # Option pour la création des fichiers de dépendance

SRC_DIR = src$(SLASH)
INC_DIR = $(SRC_DIR)$(SLASH)header$(SLASH)

SRCS = $(wildcard $(SRC_DIR)*.c) # Liste de toutes les source
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS = $(patsubst $(SRC_DIR)%.c,$(DEP_DIR)%.d,$(SRCS))
EXEC = $(BIN_DIR)app


all: $(EXEC)
	@echo "All done !"


ifeq ($(MAKECMDGOALS),clean)
else ifeq ($(MAKECMDGOALS),mrproper)
else
-include $(DEPS)
endif

##### Création de l'application #####
$(EXEC): $(OBJS) | $(BIN_DIR)
	@echo "--> Linking of all objects files to build $@ ..."
	@$(LD) $(LDFLAGS) $^ -o $@

##### Création des fichiers objet #####
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "--> Compile $(patsubst $(OBJ_DIR)%.o,$(SRC_DIR)%.c,$@) to $@ ..."
	@$(CC) $(CFLAGS) -c $< -o $@

##### Création des fichiers de dépendance #####
#$(DEP_DIR)%.d: 
$(DEP_DIR)%.d: $(SRC_DIR)%.c | $(DEP_DIR)
	@echo "--> Find and put $(patsubst $(DEP_DIR)%.d,$(SRC_DIR)%.c,$@) dependences into $@ ..."; \
	$(CC) $(DEPFLAGS) $< > $(DEP_DIR)%.$$$$; \
	sed -re 's,(.*)\.o[:]+,$(BIN_DIR)\1.o $@:,g' < $(DEP_DIR)%.$$$$ > $@; \
	rm -f $(DEP_DIR)%.$$$$;


##### Création des dossiers manquant #####

$(BIN_DIR): | $(BIN_DIR_ALL)
	@echo "--> Make directory $@ ..."
	@mkdir $@

$(BIN_DIR_ALL):
	@echo "--> Make directory $@ ..."
	@mkdir $@

$(OBJ_DIR): | $(OBJ_DIR_ALL)
	@echo "--> Make directory $@ ..."
	@mkdir $@

$(OBJ_DIR_ALL):
	@echo "--> Make directory $@ ..."
	@mkdir $@

$(DEP_DIR): | $(DEP_DIR_ALL)
	@echo "--> Make directory $@ ..."
	@mkdir $@

$(DEP_DIR_ALL):
	@echo "--> Make directory $@ ..."
	@mkdir $@



.PHONY: clean
clean:
	@echo "--> Deleting objects files in objects folder $(OBJ_DIR) ..."
	@$(RM_FILE) $(OBJ_DIR)*.o*
	@echo "--> Deleting dependences files in dependences folder $(DEP_DIR) ..."
	@$(RM_FILE) $(DEP_DIR)*.d*

.PHONY: mrproper
mrproper: clean
	@echo "--> Deleting executables files in executables folder $(BIN_DIR) ..."
	@$(RM_FILE) $(EXEC)*


##### AUTO VAR #####
#
# $@  Le nom de la cible
# $<  Le nom de la première dépendance
# $^  La liste des dépendances
# %   Jocker dans un pattern : si la cible est xxA.w alors xx%.w avec % = A