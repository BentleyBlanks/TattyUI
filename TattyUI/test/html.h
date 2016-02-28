#include <TattyUI/TattyUI.h>
#include <gumbo.h>
#include <sys/stat.h>
#include <algorithm>
#include <fstream>

using namespace TattyUI;

//#define CUSTOM_WINDOW
#define HTMPPARSER_T2HTML_TEST
//#define HTMLPARSER_GETTITLE_TEST
//#define HTMLPARSER_POSITIONSOFCLASS_TEST

#ifdef HTMLPARSER_POSITIONSOFCLASS_TEST 
static std::string find_line(const std::string& original_text, const GumboAttribute& attr)
{
    size_t attr_index = attr.original_value.data - original_text.data();
    size_t begin = original_text.rfind("\n", attr_index) + 1;
    size_t end = original_text.find("\n", attr_index);

    if(end != std::string::npos)
        end--;
    else
        end = (size_t) original_text.length() - 1;

    end = min(end, attr_index + 40);
    begin = max(begin, attr_index - 40);

    return original_text.substr(begin, end - begin);
}

static void search_for_class(GumboNode* node, const std::string& original_text, const char* cls_name)
{
    if(node->type != GUMBO_NODE_ELEMENT) return;

    GumboAttribute* cls_attr;
    if((cls_attr = gumbo_get_attribute(&node->v.element.attributes, "class")) && strstr(cls_attr->value, cls_name) != NULL)
    {
        std::cout << cls_attr->value_start.line << ":"
            << cls_attr->value_start.column << " - "
            << find_line(original_text, *cls_attr) << std::endl;
    }

    GumboVector* children = &node->v.element.children;
    for(int i = 0; i < children->length; ++i)
        search_for_class(static_cast<GumboNode*>(children->data[i]), original_text, cls_name);
}

int main(int argc, char** argv)
{
    const char* filename = "../bin/script/html/index.html";
    const char* cls = "post-header";

    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if(!in)
    {
        std::cout << "File " << filename << " not found!\n";
        exit(EXIT_FAILURE);
    }

    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    // If you used contents.c_str(), it'd be harder to match up original
    // positions, because c_str() creates a copy of the string and you can't do
    // pointer arithmetic betweent contents.data() and the original_* pointers.
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, contents.data(), contents.length());
    search_for_class(output->root, contents, cls);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    getchar();
}

#endif

#ifdef HTMLPARSER_GETTITLE_TEST
static void read_file(FILE* fp, char** output, int* length)
{
    struct stat filestats;
    int fd = fileno(fp);
    fstat(fd, &filestats);
    *length = filestats.st_size;
    *output = (char*) malloc(*length + 1);
    int start = 0;
    int bytes_read;
    while((bytes_read = fread(*output + start, 1, *length - start, fp)))
    {
        start += bytes_read;
    }
}

static const char* find_title(const GumboNode* root)
{
    assert(root->type == GUMBO_NODE_ELEMENT);
    assert(root->v.element.children.length >= 2);

    const GumboVector* root_children = &root->v.element.children;
    GumboNode* head = NULL;
    for(int i = 0; i < root_children->length; ++i)
    {
        GumboNode* child = (GumboNode*) root_children->data[i];
        if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD)
        {
            head = child;
            break;
        }
    }
    assert(head != NULL);

    GumboVector* head_children = &head->v.element.children;
    for(int i = 0; i < head_children->length; ++i)
    {
        GumboNode* child = (GumboNode*) head_children->data[i];
        if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE)
        {
            if(child->v.element.children.length != 1)
                return "<empty title>";

            GumboNode* title_text = (GumboNode*) child->v.element.children.data[0];
            assert(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE);
            return title_text->v.text.text;
        }
    }
    return "<no title found>";
}

int main(int argc, const char** argv)
{
    const char* filename = "../bin/script/html/index.html";
    FILE* fp = fopen(filename, "r");
    if(!fp)
    {
        printf("File %s not found!\n", filename);
        exit(EXIT_FAILURE);
    }

    char* input;
    int input_length;
    read_file(fp, &input, &input_length);
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, input, input_length);

    const char* title = find_title(output->root);
    printf("%s\n", title);

    gumbo_destroy_output(&kGumboDefaultOptions, output);
    free(input);
    getchar();
}

#endif

#ifdef HTMPPARSER_T2HTML_TEST

int main()
{
#ifdef CUSTOM_WINDOW
    // window
    t2Window *w = t2Window::getInstance();
    w->setWindowRadius(7);
    w->setTitleBarHeight(48);
    w->init("TattyUI", "../resources/font/Roboto-Regular.ttf", 1280, 800, 200, 200);
#else
    t2WindowBase *window = new t2WindowBase();
    window->setResizable(true);
    window->setMode(T2_WINDOW_WINDOWED);
    window->setup(1280, 720);
    window->setPosition(50, 50);
    window->setTitle("TattyUI");
    window->initCallBack();
    window->setVeticalSync(false);
#endif
    // controller
    // renderer layout html(css) div
    t2Renderer *renderer = t2Renderer::getInstance();
    t2LayoutController* layoutController = t2LayoutController::getInstance();
    t2HTMLController* htmlController = t2HTMLController::getInstance();
    t2DivController* divController = t2DivController::getInstance();

    vector<string> htmlPaths;
    htmlPaths.push_back("../bin/script/html/index-1.html");
    htmlController->loadHTML(htmlPaths);
    htmlController->parse();

    layoutController->updateAll();

    divController->init();
    
    t2Div* menu = divController->findByID("menu_button_1");
    if(menu)
    {
        menu->mouseReleased = [divController](int x, int y, int px, int py, int button)
        {
            divController->findByID("1")->getCSS().display = !divController->findByID("1")->getCSS().display;
            divController->findByID("2")->getCSS().display = !divController->findByID("2")->getCSS().display;
            divController->findByID("3")->getCSS().display = !divController->findByID("3")->getCSS().display;
            divController->findByID("4")->getCSS().display = !divController->findByID("4")->getCSS().display;
            divController->findByID("5")->getCSS().display = !divController->findByID("5")->getCSS().display;
            divController->findByID("6")->getCSS().display = !divController->findByID("6")->getCSS().display;
            divController->findByID("7")->getCSS().display = !divController->findByID("7")->getCSS().display;

            t2Log("Menu mouse released\n");
        };
    }
    
    t2Div* menu1 = divController->findByID("menu_button_2");
    if(menu1)
    {
        menu1->mouseReleased = [divController](int x, int y, int px, int py, int button)
        {
            divController->findByID("8")->getCSS().display = !divController->findByID("8")->getCSS().display;
            divController->findByID("9")->getCSS().display = !divController->findByID("9")->getCSS().display;
            divController->findByID("10")->getCSS().display = !divController->findByID("10")->getCSS().display;
            divController->findByID("11")->getCSS().display = !divController->findByID("11")->getCSS().display;
            divController->findByID("12")->getCSS().display = !divController->findByID("12")->getCSS().display;

            t2Log("Menu mouse released\n");
        };
    }

    while(1)
    {
        renderer->clear(238, 238, 238);

        renderer->begin();

        layoutController->update();

        divController->draw();

#ifdef CUSTOM_WINDOW
        w->draw();
#endif
        renderer->end();

#ifdef CUSTOM_WINDOW
        w->window->swapBuffer();

        w->window->processEvents();
#else
        window->swapBuffer();

        window->processEvents();
#endif
    }

    getchar();
    return 0;
}

#endif