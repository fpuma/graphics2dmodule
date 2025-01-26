#pragma once

using namespace puma;
using namespace puma::nina;

class SdlTest0
{
public:
    void initTest(puma::nina::IApplication* _application)
    {
        m_windowId = _application->createSdlWindow({ 500,500,100,100 }, "AppTest0");
        auto textureManagerPtr = _application->getWindow(m_windowId)->getRenderer()->getTextureManager();
        m_texture = textureManagerPtr->loadTexture("../asset/programmerdrawing.png");

        ISdlRenderer* renderer = _application->getWindow(m_windowId)->getRenderer();
        assert(renderer->isValid());

        renderer->setDefaultBackgroundColor({ 0, 0, 0, 255 });
    }

    void updateTest(puma::nina::IApplication* _application)
    {
        ISdlWindow* window = _application->getWindow(m_windowId);

        if (nullptr == window) return;

        ISdlRenderer* renderer = window->getRenderer();
        renderer->beginRender();

        Extent textureExtent = { m_texture.getOriginalSize().width, m_texture.getOriginalSize().height, 0, 0 };
        Extent targetExtent = { 200, 200, 200, 200 };
        renderer->renderTexture(m_texture, textureExtent, targetExtent, 0.0f);

        std::vector<ScreenPos> poly = { {50,50}, {50,70}, {70,50} };
        renderer->renderSolidPolygon(poly, { 255, 255, 255, 255 });

        renderer->endRender();
    }

private:

    Texture m_texture;
    SdlWindowId m_windowId;
};

class SdlTest1
{
public:
    void initTest(IApplication* _application)
    {
        m_windowId = _application->createSdlWindow({ 500,500,700,100 }, "AppTest2");

        auto textureManagerPtr = _application->getWindow(m_windowId)->getRenderer()->getTextureManager();

        //FontHandle myFont = 
        textureManagerPtr->loadFont("../asset/Blitztark_v0-Regular.ttf");
        m_text0 = textureManagerPtr->loadText({ "Short", "../asset/Blitztark_v0-Regular.ttf", Color::Green() });
        m_text1 = textureManagerPtr->loadText({ "Longer text", "../asset/Blitztark_v0-Regular.ttf", Color::Blue() });

        Texture myText3 = textureManagerPtr->loadText({ "Test text", "../asset/Blitztark_v0-Regular.ttf", Color::Blue() });
        textureManagerPtr->unloadText(myText3);

        ISdlRenderer* renderer = _application->getWindow(m_windowId)->getRenderer();
        assert(renderer->isValid());

        renderer->setDefaultBackgroundColor({ 0, 0, 0, 255 });
    }

    void updateTest(IApplication* _application)
    {
        ISdlWindow* window = _application->getWindow(m_windowId);

        if (nullptr == window) return;

        ISdlRenderer* renderer = window->getRenderer();
        renderer->beginRender();

        Extent textureExtent = { m_text0.getOriginalSize().width, m_text0.getOriginalSize().height, 0, 0 };
        Extent textureExtent2 = { m_text1.getOriginalSize().width, m_text1.getOriginalSize().height, 0, 0 };

        float textAspectRatio = (float)m_text0.getOriginalSize().width / (float)m_text0.getOriginalSize().height;
        Extent targetExtent = { (s32)(60 * textAspectRatio), 60, 50, 50 };
        renderer->renderTexture(m_text0, textureExtent, targetExtent, 0.0f);

        float text2AspectRatio = (float)m_text1.getOriginalSize().width / (float)m_text1.getOriginalSize().height;
        targetExtent = { (s32)(text2AspectRatio * 60), 60, 50, 125 };
        renderer->renderTexture(m_text1, textureExtent2, targetExtent, 0.0f);
        renderer->renderCircle(ScreenPos{ 250,250 }, 25, Color::White());

        renderer->endRender();
    }

private:

    Texture m_text0;
    Texture m_text1;
    
    SdlWindowId m_windowId;
};

class OglTest0
{
public:

    void initTest(IApplication* _application)
    {
        m_windowId = _application->createOglWindow({ 500,500,100,650 }, "OglWindow");
    }

    void updateTest(IApplication* _application)
    {
        IOglWindow* oglWindow = _application->getWindow(m_windowId);

        if (nullptr == oglWindow) return;

        oglWindow->getRenderer()->beginRender();
        oglWindow->getRenderer()->endRender();
    }

private:

    OglWindowId m_windowId;
};