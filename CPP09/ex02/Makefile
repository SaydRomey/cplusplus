
NAME		:=	PmergeMe
AUTHOR		:=	cdumais

COMPILE		:=	c++
C_FLAGS		:=	-Wall -Wextra -Werror
STANDARD	:=	-std=c++98

INC_DIR		:=	inc
INCS		:=	$(wildcard $(INC_DIR)/*.hpp)
TPP_FILES	:=	$(wildcard $(INC_DIR)/*.tpp)
HEADERS		:=	-I$(INC_DIR)

SRC_DIR		:=	src
SRCS		:=	$(wildcard $(SRC_DIR)/*.cpp)

OBJ_DIR		:=	obj
OBJS		:=	$(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TMP_DIR		:=	tmp
TMP_FILES	:=	# If files are created outside of TMP_DIR folder

REMOVE		:=	rm -rf
OS			:=	$(shell uname)
NPD			:=	--no-print-directory

# Redirection variables
STDOUT_NULL		:= >/dev/null
STDERR_STDOUT	:= 2>&1
IN_BACKGROUND	:= &

# Detect OS and define OPEN command
ifeq ($(OS), Darwin)
	OPEN := open
else
	OPEN := xdg-open
endif

# Conditional flag for Linux to allow implicit fall-through in switch statements
ifeq ($(OS), Linux)
	C_FLAGS += -Wno-error=implicit-fallthrough -Wimplicit-fallthrough=0
endif

# **************************************************************************** #

all: $(NAME) ## Compile the Project and create the executable

$(NAME): $(OBJS) $(INCS) $(TPP_FILES)
	@echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)]\\t$(GREEN)ready$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(STANDARD) $(OBJS) $(HEADERS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCS) $(TPP_FILES) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(STANDARD) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean: ## Remove folder containing object files
	@if [ -n "$(wildcard $(OBJ_DIR))" ]; then \
		$(REMOVE) $(OBJ_DIR); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Object files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No object files to remove$(RESET)"; \
	fi

fclean: clean ## 'clean' + Remove executable
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Executable removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No executable to remove$(RESET)"; \
	fi

re: fclean all ## 'fclean' + 'all' (Recompile the project)

.PHONY: all clean fclean re
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
.DEFAULT_GOAL	:= all

.DEFAULT: ## Handle invalid targets
	$(info make: *** No rule to make target '$(MAKECMDGOALS)'.  Stop.)
	@$(MAKE) help $(NPD)

help: ## Display available targets
	@echo "\nAvailable targets:"
	@awk 'BEGIN {FS = ":.*##";} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "  $(CYAN)%-15s$(RESET) %s\n", $$1, $$2 \
		} \
		/^##@/ { \
			printf "\n$(BOLD)%s$(RESET)\n", substr($$0, 5) \
		}' $(MAKEFILE_LIST)

GENERATED_SEQUENCE	:= $(TMP_DIR)/generated_sequence.txt
SEQUENCE_HYPERLINK	:= \033]8;;file://$(GENERATED_SEQUENCE)\a$(GENERATED_SEQUENCE)\033]8;;\a

rand: all | $(TMP_DIR)
	@read -p "How many values should we generate for $(NAME)? " NUM_VALUES; \
	if [ -z "$$NUM_VALUES" ]; then \
		echo "No value entered. Running $(NAME) without arguments."; \
		./$(NAME); \
	elif [ $$NUM_VALUES -gt 0 ]; then \
		if [ "$(shell uname)" = "Linux" ]; then \
			RAND_SEQUENCE=$$(shuf -i 1-$$NUM_VALUES -n $$NUM_VALUES | tr '\n' ' '); \
		else \
			RAND_SEQUENCE=$$(awk -v n=$$NUM_VALUES 'BEGIN{srand(); max=2*n; \
				for(i=0; i<n; i++) { \
					do { \
						r=int(rand()*max); \
					} while(r in seen || r < 0); \
					seen[r]=1; \
					printf r" "; \
				} \
			}'); \
		fi; \
		printf "$(UP)$(ERASE_LINE)"; \
		if [ $$NUM_VALUES -gt 40 ]; then \
			echo $$RAND_SEQUENCE > $(GENERATED_SEQUENCE); \
			echo "Generated input sequence written in $(BLUE)$(SEQUENCE_HYPERLINK)$(RESET)\n"; \
		fi; \
		./$(NAME) $$RAND_SEQUENCE; \
	else \
		echo "Error: Invalid number of values, must be greater than 0."; \
		exit 1; \
	fi

# RAND_SEQUENCE=$$(awk -v n=$$NUM_VALUES 'BEGIN{srand(); for(i=1; i<=n; i++) a[i]=i; for(i=n; i>0; i--){j=int(rand()*i)+1; printf a[j]" "; a[j]=a[i]}}'); # <- N shuffled numbers from 1 to N
# RAND_SEQUENCE=$$(awk -v n=$$NUM_VALUES 'BEGIN{srand(); max=2*n; for(i=0; i<n; i++){do{r=int(rand()*max)} while(r in seen || r < 0); seen[r]=1; printf r" "}}'); <- N shuffled numbers from 0 to N*2 ?

run: rand ## Compile and run the executable with randomized sequence argument

debug: C_FLAGS += -DDEBUG=true
debug: re ## 're' + Set 'DEBUG' macro to 'true' to print more info in executable

$(TMP_DIR):
	@mkdir -p $(TMP_DIR)

ffclean: fclean ## 'fclean' + Remove temporary files and folders
	@if [ -n "$(wildcard $(TMP_DIR))" ]; then \
		$(REMOVE) $(TMP_DIR); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Temporary files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No temporary files to remove$(RESET)"; \
	fi
	@$(REMOVE) out.txt

.PHONY: help rand run debug ffclean
# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
GIT_URL		:= https://github.com/SaydRomey/42_ressources

pdf: ## Obtain the PDF instructions for this project and open it
	@echo "Obtaining pdf..."
	@$(MAKE) get_pdf MODULE=cpp09 $(NPD)

get_pdf: | $(TMP_DIR)
	@PDF=$(MODULE)_en.pdf; \
	PDF_URL=$(GIT_URL)/blob/main/pdf/CPP/$$PDF?raw=true; \
	curl -# -L $$PDF_URL -o $(TMP_DIR)/$$PDF; \
	$(OPEN) $(TMP_DIR)/$$PDF

.PHONY: pdf get_pdf
# **************************************************************************** #
# ------------------------------ DOCUMENTATION ------------------------------- #
# **************************************************************************** #
CPP_REF_URL		:=	https://cplusplus.com/reference/
CPP_TUTO_URL	:=	https://cplusplus.com/doc/oldtutorial/

ref: ## Open documentation (https://cplusplus.com/reference/)
	@echo "Opening cplusplus reference's url..."
	@$(OPEN) $(CPP_REF_URL) $(STDOUT_NULL) $(STDERR_STDOUT) $(IN_BACKGROUND)

tuto: ## Open tutorial (https://cplusplus.com/doc/oldtutorial/)
	@echo "Opening cplusplus oldtutorial's url..."
	@$(OPEN) $(CPP_TUTO_URL) $(STDOUT_NULL) $(STDERR_STDOUT) $(IN_BACKGROUND)

.PHONY: ref tuto
# **************************************************************************** #
# --------------------------------- GITHUB ----------------------------------- #
# **************************************************************************** #
REPO_LINK	:= https://github.com/SaydRomey/CPP

repo: ## Open author's CPP repo on github
	@echo "Opening $(AUTHOR)'s github repo..."
	@$(OPEN) $(REPO_LINK) $(STDOUT_NULL) $(STDERR_STDOUT) $(IN_BACKGROUND)

gitignore: ## Create the .gitignore file with multi-line variable in 'TEMPLATES' section
	@echo "Creating gitignore file..."
	@echo "$$GITIGNORE_CONTENT" > .gitignore

.PHONY: repo gitignore
# **************************************************************************** #
# --------------------------------- CLASS ------------------------------------ #
# **************************************************************************** #
class: ## Script to automate class creation
	@echo "Enter the class name: "; \
	read classname; \
	classname_upper=`echo $$classname | tr a-z A-Z`; \
	if [ -f inc/$$classname.hpp ] || [ -f src/$$classname.cpp ]; then \
		read -p "Files exist. Overwrite? [y/N]: " confirm; \
		if [ "$$confirm" != "y" ] && [ "$$confirm" != "Y" ]; then \
			echo "Canceling class creation"; \
			exit 1; \
		fi; \
	fi; \
	mkdir -p $(INC_DIR) $(SRC_DIR); \
	echo "$$CLASS_HEADER" \
	| sed "s/CLASSNAME_UPPER/$$classname_upper/g" \
	| sed "s/CLASSNAME/$$classname/g" > inc/$$classname.hpp; \
	echo "$$CLASS_CPP" \
	| sed "s/CLASSNAME/$$classname/g" > src/$$classname.cpp; \
	if [ -f $(SRC_DIR)/main.cpp ]; then \
		awk 'BEGIN {count=0} \
			/^$$/ {count++} \
			{print} \
			count==1 && !printed {print "#include \"'$$classname'.hpp\""; printed=1}' \
			$(SRC_DIR)/main.cpp > $(SRC_DIR)/tmp && mv $(SRC_DIR)/tmp $(SRC_DIR)/main.cpp; \
	fi; \
	echo "$$classname created"

.PHONY: class
# **************************************************************************** #
# ------------------------------- TEMPLATES ---------------------------------- #
# **************************************************************************** #
define GITIGNORE_CONTENT
# object files and archives in all directories
*.o
*.a

# PDFs
*.pdf

# macOS specific files
*.dSYM
.DS_Store

# Visual Studio Code settings
.vscode

# tmp, and obj directories in all directories
**/tmp/
**/obj/

# output files
out.txt

# # Executables

# Default executable
a.out

# $(MODULE) specific executables
$(NAME)

endef

export GITIGNORE_CONTENT
# **************************************************************************** #
# **************************************************************************** #
define CLASS_HEADER
#ifndef CLASSNAME_UPPER_HPP
# define CLASSNAME_UPPER_HPP

# include <iostream>

# define RESET		"\\033[0m"
# define RED		"\\033[91m"
# define GREEN		"\\033[32m"
# define YELLOW		"\\033[33m"
# define PURPLE		"\\033[95m"
# define ORANGE		"\\033[38;5;208m"
# define GRAYTALIC	"\\033[3;90m"

class CLASSNAME
{
	private:
		// Attributes
	
	public:
		// Constructors / Destructors
		CLASSNAME(void);
		CLASSNAME(const CLASSNAME &other);
		~CLASSNAME(void);

		// Getters / Setters

		// Functions / Methods

		// Operators
		CLASSNAME&	operator=(const CLASSNAME &other);

		// Exceptions
};

// std::ostream&	operator<<(std::ostream &out, const CLASSNAME &param);

#endif // CLASSNAME_UPPER_HPP
endef

export CLASS_HEADER
# **************************************************************************** #
# **************************************************************************** #
define CLASS_CPP
#include "CLASSNAME.hpp"

/* ************************************************************************** */ // Constructors / Destructors

CLASSNAME::CLASSNAME(void)
{
	std::cout << GRAYTALIC << "CLASSNAME [default constructor]" << RESET << std::endl;
}

CLASSNAME::CLASSNAME(const CLASSNAME &other)
{
	*this = other;
	std::cout << GRAYTALIC << "CLASSNAME [copy constructor]" << RESET << std::endl;
}

CLASSNAME::~CLASSNAME(void)
{
	std::cout << GRAYTALIC << "CLASSNAME [default destructor]" << RESET << std::endl;
}

/* ************************************************************************** */ // Getters / Setters

/* ************************************************************************** */ // Functions / Methods

/* ************************************************************************** */ // Operators

CLASSNAME&	CLASSNAME::operator=(const CLASSNAME &other)
{
	// if (this != &other)
	// {}
	
	return (*this);
}

// std::ostream&	operator<<(std::ostream &out, const CLASSNAME &param)

/* ************************************************************************** */ // Exceptions

endef

export CLASS_CPP
# **************************************************************************** #
# ----------------------------------- ANSI ----------------------------------- #
# **************************************************************************** #
ESC			:= \033

# Text
RESET		:= $(ESC)[0m
BOLD		:= $(ESC)[1m
ITALIC		:= $(ESC)[3m
UNDERLINE	:= $(ESC)[4m

RED			:= $(ESC)[91m
GREEN		:= $(ESC)[32m
YELLOW		:= $(ESC)[93m
ORANGE		:= $(ESC)[38;5;208m
BLUE		:= $(ESC)[94m
PURPLE		:= $(ESC)[95m
CYAN		:= $(ESC)[96m
GRAYTALIC	:= $(ESC)[3;90m

# Cursor movement
UP			:= $(ESC)[A

# Erasing
ERASE_LINE	:= $(ESC)[2K

# Hyperlinks (w.i.p)
# HYPERLINK			:= \033]8;;
# usage: $(HYPERLINK)file://$(FILEPATH)\a$(FILEPATH)$(HYPERLINK)\a
