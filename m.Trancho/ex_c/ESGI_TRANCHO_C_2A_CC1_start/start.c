/* Commande de compilation via MSYS2 MinGW 64 : */
/* gcc start.c -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_gfx */

#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 1024;
const int hauteur = 512;
const char * titre = "ESGI image simplification";
const char * target_image = "fibo.jpg";
const char * quadtree_save = "image.quadtree";
SDL_Surface * ecran = NULL;

int max_depth = -1;
int visualize = 0;
float simplify_coeff = 0.1;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#define RSHIFT 24
#define GSHIFT 16
#define BSHIFT 8
#define ASHIFT 0
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#define RSHIFT 0
#define GSHIFT 8
#define BSHIFT 16
#define ASHIFT 24
#endif

typedef struct Color Color;
struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

Color get_pixel(SDL_Surface * surface, int x, int y) {
	Uint8 *p = (Uint8*)surface->pixels + (y * surface->pitch + x * surface->format->BytesPerPixel);
	Uint32 px = *(Uint32*)p;
	return (Color) {
		.r = (px >> RSHIFT) & 0xff,
		.g = (px >> GSHIFT) & 0xff,
		.b = (px >> BSHIFT) & 0xff,
		.a = (px >> ASHIFT) & 0xff
	};
}

typedef struct Node Node;
struct Node{
	int is_leaf;
	Color color;
	Node * children[4];
}; 

typedef struct Image Image;
struct Image {
	SDL_Surface * surface;
	Node * quadtree;
};
Node *recursuive_compute(SDL_Surface *surface,int x, int y, int width,int height);
void compute_quadtree(Image * image);
float calculate_variance(Node* node);
Node* copy_node(Node* source) ;
void recursive_simplify(Node* node, float coef);
void simplify_quadtree(Image* image);
void reset_quadtree(Image* image) ;
void simplify_quadtree(Image* image);
void reset_quadtree(Image* image);
void free_quadtree(Node *new_node);
Image Image_load(const char * path);
void Image_free(Image * image) ;
void display_surface(Image * image, int offset_x, int offset_y, int width, int height) ;
void print_quadtree(Node *new_node,int x,int y,int width,int height,int current,int max);
void display_quadtree(Image * image, int offset_x, int offset_y, int width, int height, int max_depth);
void affichage(Image * image);
void save_quadtree(Image * image, const char * path) ;
void load_quadtree(Image * image, const char * path);



int main(int argc, char * argv[]) {
	
	/* Création d'une fenêtre SDL : */
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	char caption[256];
	sprintf(caption, "%s (simplify at %.2f %%)", titre, simplify_coeff * 100.);
	SDL_WM_SetCaption(caption, NULL);
	
	Image image = Image_load(argc == 1 ? target_image : argv[1]);
	
	int active = 1;
	SDL_Event event;
	
	while(active) {
		
		affichage(&image);
		SDL_Flip(ecran);
		
		SDL_WaitEvent(&event);
		
		switch(event.type) {
			/* Utilisateur clique sur la croix de la fenêtre : */
			case SDL_QUIT : {
				active = 0;
			} break;
			
			/* Utilisateur enfonce une touche du clavier : */
			case SDL_KEYDOWN : {
				switch(event.key.keysym.sym) {
					/* Touche Echap : */
					case SDLK_ESCAPE : {
						active = 0;
					} break;
					
					default : break;
				}
			} break;
			
			case SDL_KEYUP : {
				switch(event.key.keysym.sym) {
					case SDLK_LEFT : {
						if(max_depth > -1) --max_depth;
					} break;
					
					case SDLK_RIGHT : {
						++max_depth;
					} break;
					
					case SDLK_SPACE : {
						reset_quadtree(&image);
					};
					
					case SDLK_UP : {
						simplify_coeff *= 1.1;
						sprintf(caption, "%s (simplify at %.2f %%)", titre, simplify_coeff * 100.);
						SDL_WM_SetCaption(caption, NULL);
						reset_quadtree(&image);
						simplify_quadtree(&image);
					} break;
					
					case SDLK_DOWN : {
						simplify_coeff /= 1.1;
						sprintf(caption, "%s (simplify at %.2f %%)", titre, simplify_coeff * 100.);
						SDL_WM_SetCaption(caption, NULL);
						reset_quadtree(&image);
						simplify_quadtree(&image);
					} break;
					
					case SDLK_v : {
						visualize = ! visualize;
					} break;
					
					case SDLK_x : {
						reset_quadtree(&image);
						simplify_quadtree(&image);
					} break;
					
					case SDLK_s : {
						save_quadtree(&image, quadtree_save);
					} break;
					
					case SDLK_l : {
						load_quadtree(&image, quadtree_save);
					} break;
					
					default : break;
				}
			} break;
			
			default : break;
		}
	}
	
	Image_free(&image);
	
	SDL_FreeSurface(ecran);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}


Node *recursuive_compute(SDL_Surface *surface,int x, int y, int width,int height){
	Node *new_node= (Node *)malloc(sizeof(Node));
	if(new_node==NULL){
		return 0;
	}
	new_node->is_leaf=0;
	for(int i=0;i<4;i++){
	new_node->children[i]=NULL;
	}
	if(width==1 && height==1){
		new_node->color=get_pixel(surface,x,y);
		new_node->is_leaf=1;
	}else{
	int	half_w=width/2;
	int	half_h=height/2;
		if(half_w>0&&half_h>0){
			new_node->children[0]=recursuive_compute(surface,x,y,half_w,half_h);
			new_node->children[1]=recursuive_compute(surface,x+half_w,y,half_w,half_h);
			new_node->children[2]=recursuive_compute(surface,x,y+half_h,half_w,half_h);
			new_node->children[3]=recursuive_compute(surface,x+half_w,y+half_h,half_w,half_h);
		}
		new_node->color.r=(new_node->children[0]->color.r+new_node->children[1]->color.r+new_node->children[2]->color.r+new_node->children[3]->color.r)/4;
		new_node->color.g=(new_node->children[0]->color.g+new_node->children[1]->color.g+new_node->children[2]->color.g+new_node->children[3]->color.g)/4;
		new_node->color.b=(new_node->children[0]->color.b+new_node->children[1]->color.b+new_node->children[2]->color.b+new_node->children[3]->color.b)/4;
		new_node->color.a=(new_node->children[0]->color.a+new_node->children[1]->color.a+new_node->children[2]->color.a+new_node->children[3]->color.a)/4;
	}
	return new_node;
}
void compute_quadtree(Image * image) {
	image->quadtree=recursuive_compute(image->surface,0,0,image->surface->w,image->surface->h);

}
float calculate_variance(Node* node) {
    if (node->is_leaf || !node->children[0]) return 0;
    
    float r_var = 0, g_var = 0, b_var = 0, a_var = 0;
    
    for (int i = 0; i < 4; i++) {
        r_var += pow(node->children[i]->color.r - node->color.r, 2);
        g_var += pow(node->children[i]->color.g - node->color.g, 2);
        b_var += pow(node->children[i]->color.b - node->color.b, 2);
        a_var += pow(node->children[i]->color.a - node->color.a, 2);
    }
    
    // Calculate root mean square difference
    return sqrt((r_var + g_var + b_var + a_var) / 16); // Divide by 16 (4 children * 4 channels)
}
Node* copy_node(Node* source) {
    if (!source) return NULL;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    new_node->is_leaf = source->is_leaf;
    new_node->color = source->color;
    
    if (!source->is_leaf) {
        for (int i = 0; i < 4; i++) {
            new_node->children[i] = copy_node(source->children[i]);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            new_node->children[i] = NULL;
        }
    }
    
    return new_node;
}
void recursive_simplify(Node* node, float coef) {
    if (!node || node->is_leaf) return;
    
    // First, simplify children
    for (int i = 0; i < 4; i++) {
        recursive_simplify(node->children[i], coef);
    }
    
    // Calculate variance between this node and its children
    float variance = calculate_variance(node);
    
    // If variance is below coef, merge children into parent
    if (variance < (255.0 * coef)) {
        // Free children and mark as leaf
        for (int i = 0; i < 4; i++) {
            if (node->children[i]) {
                free_quadtree(node->children[i]);
                node->children[i] = NULL;
            }
        }
        node->is_leaf = 1;
    }
}

void simplify_quadtree(Image* image) {
    // Make sure we have a valid quadtree
    if (!image || !image->quadtree) return;
    
    // Start recursive simplification
    recursive_simplify(image->quadtree, simplify_coeff);
}

void reset_quadtree(Image* image) {
    // Free the current quadtree
    if (image->quadtree) {
        free_quadtree(image->quadtree);
    }
    
    // Recompute the quadtree from the original surface
    compute_quadtree(image);
}
void free_quadtree(Node *new_node){
	if(new_node==NULL)return;
	if(new_node->is_leaf==0){
		for(int i=0;i<4;i++){
			free_quadtree(new_node->children[i]);
			new_node->children[i]=NULL;
		}
	}
	free(new_node);
}
Image Image_load(const char * path) {
	Image image;
	image.surface=IMG_Load(path);
	if(image.surface==NULL){
		fprintf(stderr,"unable to read from the image  %s",IMG_GetError());
		exit(EXIT_FAILURE);
	}
	compute_quadtree(&image);
	return image;
}

void Image_free(Image * image) {
	/* TODO : libérer l'image et le quadtree associé. */
	SDL_FreeSurface(image->surface);
	free_quadtree(image->quadtree);
}
void display_surface(Image * image, int offset_x, int offset_y, int width, int height) {
	/* TODO : afficher l'image à la position (offset_x, offset_y) */
	/* en tronquant si elle dépasse les dimensions (width, height). */
	SDL_Rect src = {0, 0, width, height};
	SDL_Rect quad = {offset_x,offset_y,width,height};
	SDL_BlitSurface(image->surface,&src,ecran,&quad);
}
void print_quadtree(Node *new_node,int x,int y,int width,int height,int current,int max){
	if(new_node==NULL)return;
	if(current>max)return;
	if(current==max){
		boxRGBA(ecran,x,y,x+width-1,y+height-1,new_node->color.r,new_node->color.g,new_node->color.b,255);
		if(visualize){
			rectangleRGBA(ecran,x,y,x+width-1,y+height-1,0,0,0,255);
		}
	}else{
		int h_w=width/2;
		int h_h=height/2;
		print_quadtree(new_node->children[0],x,y,h_w,h_h,current+1,max);
		print_quadtree(new_node->children[1],x+h_w,y,h_w,h_h,current+1,max);
		print_quadtree(new_node->children[2],x,y+h_h,h_w,h_h,current+1,max);
		print_quadtree(new_node->children[3],x+h_w,y+h_h,h_w,h_h,current+1,max);
	}
}
void display_quadtree(Image * image, int offset_x, int offset_y, int width, int height, int max_depth) {
	/* TODO : afficher le quadtree sans la zone de la position (offset_x, offset_y) */
	/* avec les dimensions (width, height). */
	print_quadtree(image->quadtree,offset_x,offset_y,width,height,0,max_depth);
}

void affichage(Image * image) {
	display_surface(image, 0, 0, largeur / 2, hauteur);
	display_quadtree(image, largeur / 2, 0, largeur / 2, hauteur, max_depth);
}

void save_quadtree(Image * image, const char * path) {

}

void load_quadtree(Image * image, const char * path) {

}