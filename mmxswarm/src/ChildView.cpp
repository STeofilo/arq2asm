// ChildView.cpp : implementation of the CChildView class 
// 
// This is a part of the Microsoft Foundation Classes C++ library. 
// Copyright (c) Microsoft Corporation.  All rights reserved. 
// 
// This source code is only intended as a supplement to the 
// Microsoft Foundation Classes Reference and related 
// electronic documentation provided with the library. 
// See these sources for detailed information regarding the 
// Microsoft Foundation Classes product. 
// 
 
#include "stdafx.h" 
 
// Grupo 16 
#ifdef USE_OPENCV 
#include "Webcam.h" 
#endif 
 
#include "MMXSwarm.h" 
#include "ChildView.h" 
 
#include "MMXSurface.h" 
#include "SSE2Surface.h" 
#include "Swarm.h" 
 
#ifdef _DEBUG 
#define new DEBUG_NEW 
#undef THIS_FILE 
static char THIS_FILE[] = __FILE__; 
#endif 
 
///////////////////////////////////////////////////////////////////////////// 
// CChildView 
BEGIN_MESSAGE_MAP(CChildView, CWnd) 
    ON_WM_PAINT() 
    ON_WM_SETCURSOR() 
    ON_WM_TIMER() 
    ON_WM_SIZE() 
    ON_COMMAND(ID_FILE_OPEN, OnFileOpen) 
    ON_COMMAND(ID_FILE_SAVE, OnFileSave) 
    ON_COMMAND(ID_VIEW_PAUSE_BLUR, OnViewPauseBlur) 
    ON_COMMAND(ID_VIEW_PAUSE_SWARM, OnViewPauseSwarm) 
    ON_COMMAND(ID_VIEW_PAUSE_BLIT, OnViewPauseBlit) 
    ON_COMMAND(ID_VIEW_USE_FADE, OnViewUseFade) 
    ON_COMMAND(ID_VIEW_USE_GRAY, OnViewUseGray)    //Grupo 4 
    //ON_COMMAND(ID_VIEW_USE_GRADIENT, OnViewUseGradient)    //Grupo 8 
    ON_COMMAND(ID_VIEW_USE_THRESHOLD, OnViewUseThreshold) //grupo 13 
    ON_COMMAND(ID_VIEW_USE_SOBEL, OnViewUseSobel)//Grupo 5 
    ON_COMMAND(ID_VIEW_USE_AZULAR, OnViewUseAzular)    //Grupo 5 
    ON_COMMAND(ID_VIEW_USE_ESVERDEAR, OnViewUseEsverdear)    //Grupo 5 
    ON_COMMAND(ID_VIEW_USE_ENVERMELHAR, OnViewUseEnvermelhar)    //Grupo 5 
    ON_COMMAND(ID_VIEW_USE_POSTERIZE, OnViewUsePosterize)//Grupo 9 
    ON_COMMAND(ID_VIEW_USE_GRAYF, OnViewUseGrayF)    //Grupo 12 
    ON_COMMAND(ID_VIEW_USE_RGBADJUST, OnViewUseRGBAdjust)    //Grupo 14 
    ON_COMMAND(ID_VIEW_USE_MASK, OnViewUseMask)    //Grupo 15 
    ON_COMMAND(ID_VIEW_USE_MANDEL, OnViewUseMandel)    //Grupo 6 
    ON_COMMAND(ID_VIEW_USE_SOLARIZE, OnViewUseSolarize)//Grupo 18 
    ON_COMMAND(ID_VIEW_USE_INVERT, OnViewUseInvert)//Grupo 7 
    ON_COMMAND(ID_VIEW_USE_CHANNELMIX, OnViewUseChannelmix) //Grupo 11 
    ON_COMMAND(ID_MODE_WEBCAM, OnModeWebcam) // Grupo 16 
    ON_COMMAND(ID_VIEW_USE_RESCALE, OnViewUseRescale)//Grupo 17 
    ON_COMMAND(ID_VIEW_USE_MIRROR, OnViewUseMirror)//Grupo 18 
    ON_COMMAND(ID_VIEW_USE_AMARELAR, OnViewUseAmarelar)    //Grupo 20
	ON_COMMAND(ID_VIEW_USE_RB3D, OnViewUseRB3D)    //Grupo 2012
	ON_COMMAND(ID_VIEW_USE_MEDIAN, OnViewUseMedian)    //Grupo 2012
	ON_COMMAND(ID_VIEW_USE_CIANO, OnViewUseCiano)/////  Rodrigo
	ON_COMMAND(ID_VIEW_USE_MAGENTA, OnViewUseMagenta)/////  Rodrigo
     
     ON_COMMAND(ID_MODE_SWARM, OnModeSWARM)
     ON_COMMAND(ID_MODE_FADE, OnModeFADE)
     ON_COMMAND(ID_MODE_IMAGE, OnModeIMG)

    ON_UPDATE_COMMAND_UI(ID_VIEW_PAUSE_BLUR, OnUpdatePauseBlur) 
    ON_UPDATE_COMMAND_UI(ID_VIEW_PAUSE_SWARM, OnUpdatePauseSwarm) 
    ON_UPDATE_COMMAND_UI(ID_VIEW_PAUSE_BLIT, OnUpdatePauseBlit) 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_FADE, OnUpdateUseFade) 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_GRAY, OnUpdateUseGray)    //Grupo 4 
   // ON_UPDATE_COMMAND_UI(ID_VIEW_USE_GRADIENT, OnUpdateUseGradient)    //Grupo 8 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_THRESHOLD, OnUpdateUseThreshold) //grupo 13 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_SOBEL, OnUpdateUseSobel)//Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_AZULAR, OnUpdateUseAzular)//Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_ESVERDEAR, OnUpdateUseEsverdear)//Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_ENVERMELHAR, OnUpdateUseEnvermelhar)//Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_POSTERIZE, OnUpdateUsePosterize)//Grupo 9 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_GRAYF, OnUpdateUseGrayF)    //Grupo 12 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_RGBADJUST, OnUpdateUseRGBAdjust)    //Grupo 14 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_MASK, OnUpdateUseMask)    //Grupo 15 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_SOLARIZE, OnUpdateUseSolarize)//Grupo 18 
	ON_UPDATE_COMMAND_UI(ID_VIEW_USE_CIANO, OnUpdateUseCiano) ////////Rodrigo
	ON_UPDATE_COMMAND_UI(ID_VIEW_USE_MAGENTA, OnUpdateUseMagenta) ////////Rodrigo
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_RESCALE, OnUpdateUseRescale)//Grupo 17 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_CHANNELMIX, OnUpdateUseChannelmix) //Grupo 11 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_MIRROR, OnUpdateUseMirror)//Grupo 18 
    ON_UPDATE_COMMAND_UI(ID_VIEW_USE_RB3D, OnUpdateUseRB3D)//Grupo 2012
	ON_UPDATE_COMMAND_UI(ID_VIEW_USE_MEDIAN, OnUpdateUseMedian)//Grupo 2012
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_PAUSE_BLUR, OnUpdatePauseBlur) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_PAUSE_SWARM, OnUpdatePauseSwarm) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_PAUSE_BLIT, OnUpdatePauseBlit) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_FADE, OnUpdateUseFade) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_GRAY, OnUpdateUseGray)    //Grupo 4 
    //ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_GRADIENT, OnUpdateUseGradient)    //Grupo 8 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_THRESHOLD, OnUpdateUseThreshold) //grupo 13 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_SOBEL, OnUpdateUseSobel) //Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_AZULAR, OnUpdateUseAzular) //Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_ESVERDEAR, OnUpdateUseEsverdear) //Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_ENVERMELHAR, OnUpdateUseEnvermelhar) //Grupo 5 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_GRAYF, OnUpdateUseGrayF)    //Grupo 12 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_RGBADJUST, OnUpdateUseRGBAdjust)//Grupo 14 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_MASK, OnUpdateUseMask)//Grupo 15 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_POSTERIZE, OnUpdateUsePosterize)//Grupo 9 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_MANDEL, OnUpdateUseMandel)//Grupo 6 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_SOLARIZE, OnUpdateUseSolarize)//Grupo 18 
	 ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_CIANO, OnUpdateUseCiano)/////////Rodrigo
	  ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_MAGENTA, OnUpdateUseMagenta)/////////Rodrigo
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_RESCALE, OnUpdateUseRescale)//Grupo 17 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_INVERT, OnUpdateUseInvert)//Grupo 7 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_CHANNELMIX, OnUpdateUseChannelmix) //Grupo 11 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_MIRROR, OnUpdateUseMirror) //Grupo 18 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_AMARELAR, OnUpdateUseAmarelar) //Grupo 20 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_RB3D, OnUpdateUseRB3D) //Grupo 2012 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_MEDIAN, OnUpdateUseMedian) //Grupo 2012 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_FPS, OnUpdateFPS) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_RESOLUTION, OnUpdateResolution) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_WEBCAM, OnUpdateModeWebcam) //Grupo 16 

	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_SWARM, OnUpdateModeSwarm)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_FADE, OnUpdateModeFADE)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_USE_IMAGE, OnUpdateModeIMG)
     
 
    ON_COMMAND_RANGE(IDD_16BIT_MMXINTRINSICS, IDD_32BIT_GENERICCBLUR, OnImageFormats) 
    ON_UPDATE_COMMAND_UI_RANGE(IDD_16BIT_MMXINTRINSICS, IDD_32BIT_GENERICCBLUR, OnUpdateImageFormats) 
    ON_UPDATE_COMMAND_UI_RANGE(ID_MODE_WEBCAM, ID_MODE_SWARM, OnUpdateMode) 
    ON_WM_ERASEBKGND() 
    ON_WM_DESTROY() 
END_MESSAGE_MAP() 
 
CChildView::CChildView() 
{ 
    m_pSurface = NULL; 
    m_dwTickStart = ::GetTickCount(); 
    m_nFrameCounter = 0; 
    m_nFilterLoad = 0; 
    m_nFilterSave = 0; 
    m_bSizeChanged = false; 
    m_bPauseBlur = false;     
    m_bPauseSwarm = false; 
    m_bPauseBlit = false; 
    m_bPauseFade = false; 
    m_bUseGray = false;    //Grupo 4 
   // m_bUseGradient = false;    //Grupo 8 
	m_bUseCiano = false; ////////////////Rodrigo
	m_bUseMagenta = false; ////////////////Rodrigo
    m_bUseThreshold = false; //grupo 13 
    m_bUseSobel = false;    //Grupo 5 
    m_bUseAzular = false;    // Grupo 5 
    m_bUseEsverdear = false;    // Grupo 5 
    m_bUseEnvermelhar = false;    // Grupo 5 
    m_bUseGrayF = false;    //Grupo 12 
    m_bUseRGBAdjust = false;    //Grupo 14 
    m_bUseMask = false;    //Grupo 15 
    m_bUsePosterize = false; //Grupo 9 
    m_bUseMandel = false;    //Grupo 6 
    m_bUseChannelmix = false; //Grupo 11 
    m_bTimerPopped = false; 
    m_eSurf = eNone; 
    m_eMode = eSwarm; 
    execSobel = false; //Grupo 5 
    execGray = false; //grupo 12 
    m_bUseSolarize = false; // Grupo 18 
	
    m_bUseMirror = false; // Grupo 18 
    m_bUseInvert = false;  //GRUPO 7 
    m_bUseWebcam = false;    // Grupo 16 
    m_bUseRescale = false;  //GRUPO 17 
    m_bUseRB3D = false;  //GRUPO 2012 
	m_bUseMedian = false;  //GRUPO 2012 
	    m_bUseSWARM = false;
		m_bUseIMG = false;
		m_bUseFADE = false;
		first = true;
} 
 
CChildView::~CChildView() 
{ 
    delete m_pSurface; 
} 
 
///////////////////////////////////////////////////////////////////////////// 
// CChildView message handlers 
 
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)  
{ 
    if (!CWnd::PreCreateWindow(cs)) 
        return FALSE; 
 
    cs.dwExStyle |= WS_EX_CLIENTEDGE; 
    cs.style &= ~WS_BORDER; 
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,  
        ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL); 
 
    return TRUE; 
} 
 
void CChildView::OnFileOpen() 
{ 
    CImage image, image2; 
    CString strFilter; 
    CString strAllFilePrompt; 
    CSimpleArray<GUID> aguidFileTypes; 
    HRESULT hResult; 
    INT_PTR nResult; 
 
    if (m_pSurface == NULL) 
        return; 
    VERIFY(strAllFilePrompt.LoadString(IDS_ALL_IMAGES)); 
    hResult = image.GetImporterFilterString(strFilter, aguidFileTypes, strAllFilePrompt); 
    if(FAILED(hResult))    { 
        CString fmt; 
        fmt.Format(IDS_ERROR_GETEXPORTERFILTER, hResult, _com_error(hResult).ErrorMessage()); 
        ::AfxMessageBox(fmt); 
        return; 
    } 
 
    CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter); 
    dlg.m_ofn.nFilterIndex = m_nFilterLoad; 
 
    nResult = dlg.DoModal(); 
    if(nResult != IDOK) { 
        return; 
    } 
 
    m_nFilterLoad = dlg.m_ofn.nFilterIndex; 
    hResult = image.Load(dlg.GetPathName()); 
    ASSERT(SUCCEEDED(hResult)); 
    if (SUCCEEDED(hResult)) {         
 
        CFileDialog dlg2(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter); 
        dlg2.m_ofn.nFilterIndex = m_nFilterLoad; 
 
        nResult = dlg2.DoModal(); 
 
        if(nResult != IDOK) { 
            return; 
        } 
 
        m_nFilterLoad = dlg2.m_ofn.nFilterIndex; 
        hResult = image2.Load(dlg2.GetPathName()); 
 
        m_pSurface->Import(image, image2); 
        // Stop the weird effects 
        m_bPauseBlur = true; 
        m_bPauseSwarm = true; 
        m_bUseGray = false; 
        m_bUseInvert = false; 
        m_bPauseFade = false; 
        m_bUseRGBAdjust = false; 
        m_bUseMask = false; 
        m_bUseMandel = false; 
        m_bUsePosterize = false; 
        m_bUseSobel = false; 
        m_bUseAzular = false; 
        m_bUseEsverdear = false; 
        m_bUseEnvermelhar = false; 
        m_bUseGray = false; 
        m_bUseGrayF = false; 
        m_bUseSolarize = false; 
        m_bUseThreshold = false; 
       // m_bUseGradient = false; 
		m_bUseCiano = false; /////Rodrigo 
		m_bUseMagenta = false; /////Rodrigo
        m_bUseChannelmix = false; 
        m_bUseRescale = false; 
        m_bUseMirror = false; 
        m_bUseRB3D = false;
		m_bUseMedian = false;
		
    } 
} 
 
void CChildView::OnFileSave() 
{ 
    CString strFilter; 
    CSimpleArray<GUID> aguidFileTypes; 
    CImage *pImage; 
    CString fmt; 
    HRESULT hResult; 
    INT_PTR nResult; 
 
    pImage = m_pSurface->GetImage(); 
    ASSERT(pImage != NULL); 
    hResult = pImage->GetExporterFilterString( strFilter, aguidFileTypes ); 
    if(FAILED(hResult)) { 
        fmt.Format(IDS_ERROR_GETEXPORTERFILTER, hResult, _com_error(hResult).ErrorMessage()); 
        ::AfxMessageBox(fmt); 
        return; 
    } 
 
    CFileDialog dlg(FALSE, NULL, NULL,  
        OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter); 
    dlg.m_ofn.nFilterIndex = m_nFilterSave; 
 
    nResult = dlg.DoModal(); 
    if( nResult != IDOK ) { 
        return; 
    } 
    m_nFilterSave = dlg.m_ofn.nFilterIndex; 
    GUID guid = m_nFilterSave > 0 ? aguidFileTypes[m_nFilterSave-1] : GUID(GUID_NULL); 
    CString strFileName = dlg.GetPathName(); 
    if (dlg.GetFileExt().IsEmpty()) { 
        if (strFileName[strFileName.GetLength()-1] == '.') { 
            strFileName = strFileName.Left(strFileName.GetLength()-1); 
        } 
        CString strExt; 
        if (m_nFilterSave == 0) { 
            strExt = _T(".jpg"); // default to JPEG 
        } 
        else { 
            // Look up the first extension in the filters 
            int nCount = (m_nFilterSave*2)-1; 
            int nLeft = 0; 
            while (nCount) { 
                if (strFilter[nLeft++] == '|') { 
                    nCount--; 
                } 
            } 
            ASSERT(nLeft < strFilter.GetLength()); 
            strExt = strFilter.Tokenize(_T(";|"), nLeft).MakeLower(); 
            strExt = ::PathFindExtension(strExt); 
        } 
        strFileName += strExt; 
    } 
 
    hResult = pImage->Save(strFileName, guid); 
    if(FAILED(hResult)) { 
        fmt.Format(IDS_ERROR_SAVE, hResult, _com_error(hResult).ErrorMessage()); 
        ::AfxMessageBox(fmt); 
    } 
} 
 
void CChildView::OnImageFormats(UINT nID) 
{ 
    ASSERT((nID >= IDD_16BIT_MMXINTRINSICS) && (nID <= IDD_32BIT_GENERICCBLUR)); 
    m_eSurf = ESurface(nID); 
    CreateSurface(); 
} 
 
void CChildView::OnViewPauseBlur() 
{ 
    m_bPauseBlur = !m_bPauseBlur; 
} 
 
void CChildView::OnViewPauseSwarm() 
{ 
    m_bPauseSwarm = !m_bPauseSwarm; 
} 
 
void CChildView::OnViewPauseBlit() 
{ 
    m_bPauseBlit = !m_bPauseBlit; 
} 
 
void CChildView::OnViewUseFade() 
{ 
    m_bPauseFade = !m_bPauseFade; 
    execSobel = false;//Grupo5 
} 
 
//Grupo 4 
void CChildView::OnViewUseGray()     
{ 
    m_bUseGray = !m_bUseGray; 
} 
 
//Grupo 5 
void CChildView::OnViewUseAzular()     
{ 
    m_bUseAzular = !m_bUseAzular; 
} 
 
//Grupo 20 
void CChildView::OnViewUseAmarelar()     
{ 
    m_bUseAmarelar = !m_bUseAmarelar; 
} 
 
//Grupo 2012
void CChildView::OnViewUseRB3D()     
{ 
    m_bUseRB3D = !m_bUseRB3D; 
} 
//Grupo 2012
void CChildView::OnViewUseMedian()     
{ 
    m_bUseMedian = !m_bUseMedian; 
} 

//Grupo 5 
void CChildView::OnViewUseEsverdear()     
{ 
    m_bUseEsverdear = !m_bUseEsverdear; 
} 
 
//Grupo 5 
void CChildView::OnViewUseEnvermelhar()     
{ 
    m_bUseEnvermelhar = !m_bUseEnvermelhar; 
} 
 
//Grupo 8
/*
void CChildView::OnViewUseGradient()     
{ 
    m_bUseGradient = !m_bUseGradient; 
} 
 */
//Grupo5 
void CChildView::OnViewUseSobel() 
{ 
    m_bUseSobel = !m_bUseSobel; 
    if(m_bPauseFade || !m_bPauseSwarm) 
        execSobel = false; 
} 
 
//Grupo 9 
void CChildView::OnViewUsePosterize(){ 
    m_bUsePosterize = !m_bUsePosterize; 
} 
//Grupo 7 
void CChildView::OnViewUseInvert() 
{ 
    m_bUseInvert = !m_bUseInvert; 
} 
 
//Grupo 12 
void CChildView::OnViewUseGrayF()     
{ 
    m_bUseGrayF = !m_bUseGrayF; 
    execGray = false; 
} 
 
//Grupo 14 
void CChildView::OnViewUseRGBAdjust() 
{ 
    m_bUseRGBAdjust = !m_bUseRGBAdjust; 
} 
 
//Grupo 15 
void CChildView::OnViewUseMask() 
{ 
    m_bUseMask = !m_bUseMask; 
} 
 
//Grupo 6 
void CChildView::OnViewUseMandel() 
{ 
    m_bUseMandel = !m_bUseMandel; 
} 
 
//Grupo 18 
void CChildView::OnViewUseSolarize(){ 
    m_bUseSolarize = !m_bUseSolarize; 
} 
 
//Grupo 18 
void CChildView::OnViewUseMirror(){ 
    m_bUseMirror = !m_bUseMirror; 
} 
 
//grupo 13 
void CChildView::OnViewUseThreshold() 
{ 
    m_bUseThreshold = !m_bUseThreshold; 
} 
 
//Grupo 11 
void CChildView::OnViewUseChannelmix()     
{ 
    m_bUseChannelmix = !m_bUseChannelmix; 
} 
 
// Grupo 16 
void CChildView::OnModeWebcam() 
{ 
    m_bUseWebcam = !m_bUseWebcam; 
} 

void CChildView::OnModeSWARM() 
{ 
    m_bUseSWARM = !m_bUseSWARM; 
}

void CChildView::OnModeFADE() 
{ 
    m_bUseFADE = !m_bUseFADE; 
}

void CChildView::OnModeIMG() 
{ 
    m_bUseIMG = !m_bUseIMG; 
}
 
//Grupo 17 
void CChildView::OnViewUseRescale(){ 
    m_bUseRescale = !m_bUseRescale; 
} 
 

////////////////////Rodrigo
void CChildView::OnViewUseCiano(){ 
    m_bUseCiano = !m_bUseCiano; 
} 
 
 void CChildView::OnViewUseMagenta(){ 
    m_bUseMagenta = !m_bUseMagenta; 
} 
void CChildView::OnPaint()  
{ 
    CPaintDC dc(this); // device context for painting 
    // Do not call CWnd::OnPaint() for painting messages 
    if (m_pSurface != NULL) 
        m_pSurface->BlitBits(); 
} 
 
BOOL CChildView::OnIdle(LONG)  //1Count 
{ 
    BOOL bContinue = FALSE; 
    if (m_pSurface == NULL) 
        return(FALSE); 
 
    // Debugging helper for blur 
    //m_pSurface->Line(CPoint(160, 120), CPoint(160, 0), RGB(255, 128, 128)); 
    //m_pSurface->Line(CPoint(80, 60), CPoint(240, 60), RGB(128, 128, 255)); 
 
    if (::GetAsyncKeyState(VK_SHIFT) & 0x8000) { 
        m_pSurface->RandomLine((int)Random() << 15 | Random()); 
        bContinue = TRUE; 
    } 
    if (::GetAsyncKeyState(VK_DELETE) & 0x8000) { 
        m_pSurface->ClearBits(); 
        bContinue = TRUE; 
    } 
    if (::GetAsyncKeyState(VK_SPACE) & 0x8000) { 
        m_pSurface->RandomBits(); 
        bContinue = TRUE; 
    } 
    if (::GetAsyncKeyState(VK_UP) & 0x8000) { 
        m_pSurface->ShiftBits(); 
        bContinue = TRUE; 
    } 
 
    // The guts... 
    if (!m_bPauseBlur) { 
        m_pSurface->BlurBits(); 
        bContinue = TRUE; 
    } 
 
    if (!m_bPauseSwarm) { 
        m_swarm.Tick(); 
        bContinue = TRUE; 
    } 
 
    if (m_bPauseFade) { 
        m_pSurface->FadeInOut(); 
        bContinue = TRUE; 
    } 
 
        // Grupo 16 
#ifdef USE_OPENCV 
    if (m_bUseWebcam) { 
        CWebcam::Capture(m_pSurface); 
        bContinue = TRUE; 
    } else 
        if (!CWebcam::CaptureIsNull()) 
            CWebcam::Release(); 
#endif 
 
    //Grupo 4 
    if (m_bUseGray) { 
        m_pSurface->GrayScale(); 
        bContinue = TRUE; 
    } 
 
    //Grupo 8 
	/*
    if (m_bUseGradient) { 
        m_pSurface->Gradient(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseGradient = false; 
    } 
 */
    //Grupo5 
    if (m_bUseSobel && !execSobel) { 
        //verifica os Filtros ativos, para executar 1 ou mais vezes o Sobel 
        if(!m_bPauseFade && m_bPauseSwarm){ 
            execSobel = true; 
        }  
        m_pSurface->Sobel(); 
        bContinue = TRUE; 
    } 
 
    //Grupo 5 
    if (m_bUseAzular) { 
        m_pSurface->Azular(); 
        bContinue = TRUE; 
        m_bUseAzular = false; 
    } 
 
    //Grupo 20 
    if (m_bUseAmarelar) { 
        m_pSurface->Amarelar(); 
        bContinue = TRUE; 
        m_bUseAmarelar = false; 
    } 
 
	//Grupo 2012 
    if (m_bUseRB3D) { 
        m_pSurface->RB3D(); 
        bContinue = TRUE; 
        m_bUseRB3D = false; 
    } 

	//Grupo 2012 
    if (m_bUseMedian) { 
        m_pSurface->Median(); 
        bContinue = TRUE; 
        m_bUseMedian = false; 
    } 

    //Grupo 5 
    if (m_bUseEsverdear) { 
        m_pSurface->Esverdear(); 
        bContinue = TRUE; 
        m_bUseEsverdear = false; 
    } 
 
    //Grupo 5 
    if (m_bUseEnvermelhar) { 
        m_pSurface->Envermelhar(); 
        bContinue = TRUE; 
        m_bUseEnvermelhar = false; 
    } 
 
    //Grupo 9 
    if (m_bUsePosterize) { 
        m_pSurface->Posterize(); 
        bContinue = TRUE; 
    } 
    //Grupo 7 
   if (m_bUseInvert) { 
        m_pSurface->Invert(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseInvert = false; 
    } 
 
    //Grupo 12 
    if (m_bUseGrayF && !execGray) { 
        if(m_bPauseSwarm){ 
            execGray = true; 
        } 
        m_pSurface->GrayFilter(); 
        bContinue = TRUE; 
    } 
 
    //Grupo 14 
    if (m_bUseRGBAdjust) { 
        m_pSurface->RGBAdjust(); 
        bContinue = TRUE; 
        m_bUseRGBAdjust = false; 
    } 
 
    //Grupo 15 
    if (m_bUseMask) { 
        m_pSurface->Mask(); 
        bContinue = TRUE; 
    } 
 
    //Grupo 15 
    if (m_bUseMandel) { 
        m_pSurface->MandelBrot(); 
        bContinue = TRUE; 
    } 
 
    //Grupo 18 
    if (m_bUseSolarize) { 
        m_pSurface->Solarize(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseSolarize = false; 
    } 
     
    //Grupo 18 
    if (m_bUseMirror) { 
        m_pSurface->Mirror(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseMirror = false; 
    } 
 
    //grupo 13 
    if (m_bUseThreshold) { 
        m_pSurface->Threshold(); 
        bContinue = TRUE; 
    } 
 
    //Grupo 17 
    if (m_bUseRescale) { 
        m_pSurface->Rescale(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseRescale = false; 
    } 
 
    //Grupo 11 
    if (m_bUseChannelmix) { 
        m_pSurface->ChannelMix(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseChannelmix = false; 
    } 

	 ///////////////////////Rodrigo
    if (m_bUseCiano) { 
        m_pSurface->Ciano(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseCiano = false; 
    } 

	if (m_bUseMagenta) { 
        m_pSurface->Magenta(); 
        bContinue = TRUE; 
        if(!m_bPauseFade) 
            m_bUseMagenta = false; 
    }
 
 
    if (bContinue) { 
        m_nFrameCounter++; 
        if (!m_bPauseBlit) { 
            m_pSurface->BlitBits(); 
        } 
    } 
 
    ::GdiFlush(); 
    return(bContinue); 
} 
 
 
BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)  
{ 
    // Add your message handler code here and/or call default 
    if (nHitTest == HTCLIENT) { 
        SetCursor(LoadCursor(NULL, IDC_CROSS)); 
        return(TRUE); 
    } 
 
    return CWnd::OnSetCursor(pWnd, nHitTest, message); 
} 
 
void CChildView::OnSize(UINT nType, int cx, int cy)  
{ 
    CWnd::OnSize(nType, cx, cy); 
    if (m_hWnd && cx && cy) { 
        TRACE("OnSize: width == %d, height == %d\n", cx, cy); 
 
        // Initialize screen format 
        // First time init with an hwnd 
        if (m_eSurf == eNone) { 
            CClientDC dc(this); 
            int pixels; 
            bool bWarnDepth = false; 
            bool bWarnDebug = false; 
 
            SetTimer(m_kTimerID, m_kTimerDelay, NULL); 
            pixels = dc.GetDeviceCaps(BITSPIXEL) * dc.GetDeviceCaps(PLANES); 
            switch (pixels) { 
            case 16: 
                m_eSurf = IsSSE2() ? e16BitSSE2Intrin : 
                    IsMMX() ? e16BitMMXIntrin : e16BitGeneric; 
                break; 
            case 24: 
                m_eSurf =  IsSSE2() ? e24BitSSE2Intrin : 
                    IsMMX() ? e24BitMMXIntrin : e24BitGeneric; 
                break; 
            case 32: 
                m_eSurf =  IsSSE2() ? e32BitSSE2Intrin : 
                    IsMMX() ? e32BitMMXIntrin : e32BitGeneric; 
                break; 
            default: 
                bWarnDepth = true; 
                m_eSurf =  IsSSE2() ? e32BitSSE2Intrin : 
                    IsMMX() ? e32BitMMXIntrin : e32BitGeneric; 
                break; 
            } 
#ifdef _DEBUG 
            bWarnDebug = true; 
#endif 
            if (bWarnDepth || bWarnDebug) { 
                CString fmt; 
                if (bWarnDepth) { 
                    fmt.LoadString(IDS_WARNING_BITDEPTH); 
                } 
                if (bWarnDepth && bWarnDebug) { 
                    fmt += "\n"; 
                } 
                if (bWarnDebug) { 
                    CString temp; 
                    temp.LoadString(IDS_WARNING_DEBUG); 
                    fmt += temp; 
                } 
                //::AfxMessageBox(fmt, MB_ICONINFORMATION); 
            } 
 
        } 
 
        m_bSizeChanged = true; 
        CreateSurface(); 
    } 
} 
 
void CChildView::CreateSurface() 
{ 
    int nBits = 0; 
 
    delete m_pSurface; 
    m_pSurface = NULL; 
 
    switch (m_eSurf) { 
    case e16BitSSE2Intrin: 
        nBits = 16; 
        m_pSurface = new CSSE2Surface16Intrinsic(); 
        break; 
    case e16BitMMXIntrin: 
        nBits = 16; 
        m_pSurface = new CMMXSurface16Intrinsic(); 
        break; 
    case e16BitGeneric: 
        nBits = 16; 
        m_pSurface = new CSurface(); 
        break; 
    case e24BitSSE2Intrin: 
        nBits = 24; 
        m_pSurface = new CSSE2Surface24Intrinsic(); 
        break; 
    case e24BitMMXIntrin: 
        nBits = 24; 
        m_pSurface = new CMMXSurface24Intrinsic(); 
        break; 
    case e24BitGeneric: 
        nBits = 24; 
        m_pSurface = new CSurface(); 
        break; 
    case e32BitSSE2Intrin: 
        nBits = 32; 
        m_pSurface = new CSSE2Surface32Intrinsic(); 
        break; 
    case e32BitMMXIntrin: 
        nBits = 32; 
        m_pSurface = new CMMXSurface32Intrinsic(); 
        break; 
    case e32BitGeneric: 
        nBits = 32; 
        m_pSurface = new CSurface(); 
        break; 
    default: 
        ASSERT(FALSE); 
        break; 
 
    } 
    ASSERT(m_pSurface != NULL); 
    m_pSurface->Create(this, nBits); 
    m_pSurface->ClearBits(); 
 
    CRect cRect; 
    GetClientRect(&cRect); 
    int numLeaders = max(2, (cRect.Width()*cRect.Height())>>16); 
    int numLlamas = numLeaders*35; 
    m_swarm.Initialize(m_pSurface, numLeaders, numLlamas, cRect.Size()); 
} 
 
void CChildView::OnTimer(UINT_PTR nIDEvent) 
{ 
    nIDEvent; 
    ASSERT(nIDEvent == m_kTimerID); 
    // This only exists to kick the UI handler for fps. 
    m_bTimerPopped = true; 
} 
 
void CChildView::OnUpdateFPS(CCmdUI* pCmdUI) 
{ 
    if (!m_bTimerPopped) // Only update on regular intervals 
        return; 
 
    DWORD dwStop = max(m_dwTickStart+1, ::GetTickCount()); 
    CString fmt; 
    fmt.Format(_T("%d fps"), (m_nFrameCounter*1000L)/(dwStop-m_dwTickStart)); 
 
    m_nFrameCounter = 0; 
    m_bTimerPopped = false; 
    m_dwTickStart = dwStop; 
 
    pCmdUI->SetText(fmt); 
    pCmdUI->Enable(TRUE); 
} 
 
void CChildView::OnUpdatePauseBlur(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_PAUSE_BLUR) { 
        pCmdUI->Enable(m_bPauseBlur ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_PAUSE_BLUR); 
        pCmdUI->SetCheck(m_bPauseBlur ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
			    if(m_bUseWebcam)
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE);
} 
 
void CChildView::OnUpdatePauseSwarm(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_PAUSE_SWARM) { 
        pCmdUI->Enable(m_bPauseSwarm ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_PAUSE_SWARM); 
        pCmdUI->SetCheck(m_bPauseSwarm ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
		    if(m_bUseWebcam || m_bUseSWARM == false || m_bUseIMG == false)
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE);
} 
 
void CChildView::OnUpdatePauseBlit(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_PAUSE_BLIT) { 
        pCmdUI->Enable(m_bPauseBlit ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_PAUSE_BLIT); 
        pCmdUI->SetCheck(m_bPauseBlit ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
		    if(m_bUseWebcam)
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE);
} 
 
void CChildView::OnUpdateUseFade(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_FADE) { 
        pCmdUI->Enable(m_bPauseFade ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_FADE); 
        pCmdUI->SetCheck(m_bPauseFade ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

	    if(m_bUseWebcam || m_bUseThreshold || m_bUseFADE == false)
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE);
} 
 
//Grupo 4 
void CChildView::OnUpdateUseGray(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_GRAY) { 
        pCmdUI->Enable(m_bUseGray ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_GRAY); 
        pCmdUI->SetCheck(m_bUseGray ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

	    if(m_bUsePosterize || m_bUseRGBAdjust 
        || m_bUseSolarize || m_bUseGradient || m_bUseChannelmix || m_bUseAzular || m_bUseEsverdear 
        || m_bUseEnvermelhar ||  m_bUseMirror || m_bUseAmarelar || m_bUseRB3D  
        ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
     
} 
 
//Grupo 8 
/*
void CChildView::OnUpdateUseGradient(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_GRADIENT) { 
        pCmdUI->Enable(m_bUseGradient ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_GRADIENT); 
        pCmdUI->SetCheck(m_bUseGradient ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

		    if( m_bUseThreshold ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
 
     
} 
*/
//Grupo5 
void CChildView::OnUpdateUseSobel(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_SOBEL) { 
        pCmdUI->Enable(m_bUseSobel ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_SOBEL); 
        pCmdUI->SetCheck(m_bUseSobel ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    }

		    if(m_bUseSWARM == false  &&(  m_bUseFADE == true ||  m_bUseIMG == true || m_bUseWebcam == true) )
            pCmdUI->Enable(TRUE); 
    else 
 
            pCmdUI->Enable(FALSE); 

} 
 
//Grupo 5 
void CChildView::OnUpdateUseAzular(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_AZULAR) { 
        pCmdUI->Enable(m_bUseAzular ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_AZULAR); 
        pCmdUI->SetCheck(m_bUseAzular ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
		    if(m_bUseThreshold || m_bUseGrayF ||  m_bUseGray) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 


} 
 
//Grupo 5 
void CChildView::OnUpdateUseEsverdear(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_ESVERDEAR) { 
        pCmdUI->Enable(m_bUseEsverdear ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_ESVERDEAR); 
        pCmdUI->SetCheck(m_bUseEsverdear ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
		    if( m_bUseGrayF ||  m_bUseGray || m_bUseThreshold) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 

////////////////////////////////////////////////Rodrigo///////////////////
void CChildView::OnUpdateUseCiano(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_CIANO) { 
        pCmdUI->Enable(m_bUseCiano ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_CIANO); 
        pCmdUI->SetCheck(m_bUseCiano ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
		    if( m_bUseThreshold ||  m_bUseGray || m_bUseThreshold) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
 

void CChildView::OnUpdateUseMagenta(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_MAGENTA) { 
        pCmdUI->Enable(m_bUseMagenta ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_MAGENTA); 
        pCmdUI->SetCheck(m_bUseMagenta ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
		    if( m_bUseThreshold ||  m_bUseGray || m_bUseThreshold) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
 
//Grupo 20 
void CChildView::OnUpdateUseAmarelar(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_AMARELAR) { 
        pCmdUI->Enable(m_bUseAmarelar ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_AMARELAR); 
        pCmdUI->SetCheck(m_bUseAmarelar ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

		    if(m_bUseThreshold || m_bUseGrayF ||  m_bUseGray ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 

//Grupo 2012 
void CChildView::OnUpdateUseRB3D(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_RB3D) { 
        pCmdUI->Enable(m_bUseRB3D ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_RB3D); 
        pCmdUI->SetCheck(m_bUseRB3D ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

		    if(m_bUseThreshold || m_bUseGrayF ||  m_bUseGray ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
void CChildView::OnUpdateUseMedian(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_MEDIAN) { 
        pCmdUI->Enable(m_bUseMedian ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_MEDIAN); 
        pCmdUI->SetCheck(m_bUseMedian ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

		    if(m_bUseThreshold || m_bUseGrayF ||  m_bUseGray ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
 
//Grupo 5 
void CChildView::OnUpdateUseEnvermelhar(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_ENVERMELHAR) { 
        pCmdUI->Enable(m_bUseEnvermelhar ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_ENVERMELHAR); 
        pCmdUI->SetCheck(m_bUseEnvermelhar ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    }

		    if( m_bUseGrayF ||  m_bUseGray || m_bUseThreshold ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 


} 
 
//Grupo 7 
void CChildView::OnUpdateUseInvert(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_INVERT) { 
        pCmdUI->Enable(m_bUseInvert ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_INVERT); 
        pCmdUI->SetCheck(m_bUseInvert ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
	if( m_bUseGrayF || m_bUseRGBAdjust || m_bUseThreshold ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
//Grupo 9 
void CChildView::OnUpdateUsePosterize(CCmdUI *pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_POSTERIZE) { 
        pCmdUI->Enable(m_bUsePosterize ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_POSTERIZE); 
        pCmdUI->SetCheck(m_bUsePosterize ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

		    if( m_bUseRGBAdjust || m_bUseThreshold) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
 
//Grupo 12 
void CChildView::OnUpdateUseGrayF(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_GRAYF) { 
        pCmdUI->Enable(m_bUseGrayF ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_GRAYF); 
        pCmdUI->SetCheck(m_bUseGrayF ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    }
	    if( m_bUseRGBAdjust 
        || m_bUseSolarize || m_bUseGradient || m_bUseChannelmix || m_bUseAzular || m_bUseEsverdear 
        || m_bUseEnvermelhar ||  m_bUseMirror || m_bUseAmarelar  
        ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
     
} 
 
//Grupo 14 
void CChildView::OnUpdateUseRGBAdjust(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_RGBADJUST) { 
        pCmdUI->Enable(m_bUseRGBAdjust ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_RGBADJUST); 
        pCmdUI->SetCheck(m_bUseRGBAdjust ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
	    if( m_bUseGrayF ||  m_bUseGray || m_bUseThreshold) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
     
} 
 
//Grupo 15 
void CChildView::OnUpdateUseMask(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_MASK) { 
        pCmdUI->Enable(m_bUseMask ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_MASK); 
        pCmdUI->SetCheck(m_bUseMask ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 
 
//Grupo 6 
void CChildView::OnUpdateUseMandel(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_MANDEL) { 
        pCmdUI->Enable(m_bUseMandel ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_MANDEL); 
        pCmdUI->SetCheck(m_bUseMandel ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 
 
//Grupo 18 
void CChildView::OnUpdateUseSolarize(CCmdUI *pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_SOLARIZE) { 
        pCmdUI->Enable(m_bUseSolarize ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_SOLARIZE); 
        pCmdUI->SetCheck(m_bUseSolarize ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 

	    if(m_bUseGrayF || m_bUseThreshold) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
     
} 
 
//Grupo 18 
void CChildView::OnUpdateUseMirror(CCmdUI *pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_MIRROR) { 
        pCmdUI->Enable(m_bUseMirror ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_MIRROR); 
        pCmdUI->SetCheck(m_bUseMirror ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 
 
//Grupo 13 
void CChildView::OnUpdateUseThreshold(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_THRESHOLD) { 
        pCmdUI->Enable(m_bUseThreshold ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_THRESHOLD); 
        pCmdUI->SetCheck(m_bUseThreshold ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
 
    //CCmdUI pCmdUI2; 
    //pCmdUI2.m_nID = ID_VIEW_USE_SOBEL; 
    if(m_bUseSobel || m_bPauseFade || m_bUseGrayF || m_bUsePosterize || m_bUseGray || m_bUseRGBAdjust || m_bUseRGBAdjust 
        || m_bUseSolarize || m_bUseInvert  /*m_bUseGradient*/ || m_bUseChannelmix || m_bUseAzular || m_bUseEsverdear 
        || m_bUseEnvermelhar ||  m_bUseMirror || m_bUseAmarelar || m_bUseRB3D || m_bUseMedian 
        ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
     
} 
 
//Grupo 11 
void CChildView::OnUpdateUseChannelmix(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_CHANNELMIX) { 
        pCmdUI->Enable(m_bUseChannelmix ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_CHANNELMIX); 
        pCmdUI->SetCheck(m_bUseChannelmix ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
 
    if(  
     m_bUseSobel || m_bUseGray || m_bUseGrayF 
         
        ) 
            pCmdUI->Enable(FALSE); 
    else 
 
            pCmdUI->Enable(TRUE); 
} 
 
//Grupo 16 
void CChildView::OnUpdateModeWebcam(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_WEBCAM) { 
        pCmdUI->Enable(m_bUseWebcam ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_MODE_WEBCAM); 
        pCmdUI->SetCheck(m_bUseWebcam ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    }
} 

void CChildView::OnUpdateModeSwarm(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_SWARM) { 
        pCmdUI->Enable(m_bUseSWARM ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_MODE_SWARM); 
        pCmdUI->SetCheck(m_bUseSWARM ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 

void CChildView::OnUpdateModeFADE(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_FADE) { 
        pCmdUI->Enable(m_bUseFADE ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_MODE_FADE); 
        pCmdUI->SetCheck(m_bUseFADE ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 

void CChildView::OnUpdateModeIMG(CCmdUI* pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_IMAGE) { 
        pCmdUI->Enable(m_bUseIMG ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_MODE_IMAGE); 
        pCmdUI->SetCheck(m_bUseIMG ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 
 
//Grupo 17 
void CChildView::OnUpdateUseRescale(CCmdUI *pCmdUI) 
{ 
    if (pCmdUI->m_nID == ID_INDICATOR_USE_RESCALE) { 
        pCmdUI->Enable(m_bUseRescale ? FALSE : TRUE); 
    } 
    else { 
        ASSERT(pCmdUI->m_nID == ID_VIEW_USE_RESCALE); 
        pCmdUI->SetCheck(m_bUseRescale ? 1 : 0); 
        pCmdUI->Enable(TRUE); 
    } 
} 
 
void CChildView::OnUpdateResolution(CCmdUI* pCmdUI) 
{ 
    if (m_bSizeChanged) { 
        CString str; 
        str.Format(_T("%dx%d"), m_pSurface->GetVisibleWidth(), m_pSurface->GetVisibleHeight()); 
        pCmdUI->SetText(str); 
        m_bSizeChanged = false; 
    } 
    pCmdUI->Enable(TRUE); 
} 
 
void CChildView::OnUpdateImageFormats(CCmdUI* pCmdUI) 
{ 
    BOOL bEnable = TRUE; 
 
    switch (pCmdUI->m_nID) { 
    case IDD_16BIT_MMXINTRINSICS: 
    case IDD_24BIT_MMXINTRINSICS: 
    case IDD_32BIT_MMXINTRINSICS: 
        bEnable = IsMMX(); 
        break; 
    case IDD_16BIT_SSE2INTRINSICS: 
    case IDD_24BIT_SSE2INTRINSICS: 
    case IDD_32BIT_SSE2INTRINSICS: 
        bEnable = IsSSE2(); 
        break; 
    default: 
        break; 
    } 
    if (ESurface(pCmdUI->m_nID) == m_eSurf) 
        pCmdUI->SetCheck(1); 
    else 
        pCmdUI->SetCheck(0); 
 
    pCmdUI->Enable(bEnable); 
} 
             
void CChildView::OnUpdateMode(CCmdUI* pCmdUI)         
{                         
/*    m_eMode = EMode(pCmdUI->m_nID); 

         
    if (ESurface(pCmdUI->m_nID) == m_eMode)         
        pCmdUI->SetCheck(1);         
    else         
        pCmdUI->SetCheck(0);                 
    pCmdUI->Enable(true); */
	
	if(first == true && pCmdUI->m_nID == ID_MODE_SWARM){

		pCmdUI->SetCheck(1);
	}else{


		if(m_bUseWebcam && pCmdUI->m_nID == ID_MODE_WEBCAM){
			pCmdUI->SetCheck(1);
			first = false;
			//pCmdUI->Enable(FALSE);
			}
		else{
			if(m_bUseSWARM && pCmdUI->m_nID == ID_MODE_SWARM){
				pCmdUI->SetCheck(1);
		first = false;
				//pCmdUI->Enable(FALSE);
			}
			else{
							if(m_bUseFADE && pCmdUI->m_nID == ID_MODE_FADE){
								pCmdUI->SetCheck(1);
		first = false;
								//pCmdUI->Enable(FALSE);
							}
							else{
											if(m_bUseIMG && pCmdUI->m_nID == ID_MODE_IMAGE){
												pCmdUI->SetCheck(1);
		first = false;
												//pCmdUI->Enable(FALSE);
											}
											else{
												pCmdUI->SetCheck(0);
											}
							}
			}
		}
	}
} 
 
BOOL CChildView::OnEraseBkgnd(CDC*)  //pDC 
{ 
    return(TRUE); 
} 
 
void CChildView::OnDestroy(void) 
{ 
    CWnd::OnDestroy(); 
    KillTimer(m_kTimerID); 
} 
