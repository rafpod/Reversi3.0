//
//  LanguageManager.cpp
//  ReversiGL
//
//  Created by RafalP on 05.11.2013.
//
//

#include "LanguageManager.h"


void LanguageManager::setLang(int language){
    lang = language;
}

int LanguageManager::getLang(){
    return lang;
}


LanguageManager* LanguageManager::create(){
    
    LanguageManager* langManager = new LanguageManager();
    
    if (langManager) {
        langManager->autorelease();
        return langManager;
    }
    CC_SAFE_DELETE(langManager);
    return NULL;
    
}
/*
bool LanguageManager::init(){
    
    ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
        case kLanguageFrench:
            lang=frFR;
            break;
        case kLanguageGerman:
            lang=deDE;
            break;
        case kLanguageItalian:
            lang=itIT;
            break;
        case kLanguageSpanish:
            lang=esES;
            break;
        case kLanguageJapanese:
            lang=jaJP;
            break;
        default:
            lang=enGB;
    }

    if(lang){
        return false;
    }
    return true;
}
*/

LanguageManager::LanguageManager(){
    ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
        case kLanguageFrench:
            lang=frFR;
            break;
        case kLanguageGerman:
            lang=deDE;
            break;
        case kLanguageItalian:
            lang=itIT;
            break;
        case kLanguageSpanish:
            lang=esES;
            break;
        case kLanguageJapanese:
            lang=jaJP;
            break;
        default:
            lang=enGB;
    }

}


CCString* LanguageManager::Translate(int stringID){
    switch (lang) {
		default:
			switch (stringID) {
				case STRING_LANG:			return ccs("enGB");
				case STRING_NOTICE:			return ccs("Warning");
				case STRING_OK:				return ccs("OK");
				case STRING_ILLEGAL:		return ccs("Move not allowed!");
				case STRING_MUSTPASS:		return ccs("You have to pass.");
                case STRING_AI_MUSTPASS:	return ccs("Computer has to pass.");
				case STRING_END:			return ccs("Result");
				case STRING_WON:			return ccs("You won");
				case STRING_LOST:			return ccs("You lost");
				case STRING_DRAW:			return ccs("The game is a draw.");
				case STRING_BACK:			return ccs("Back");
				case STRING_NEW:			return ccs("New Game");
                    
                case STRING_RATETITLE:      return ccs("Rate this game!");
                case STRING_RATETHIS:       return ccs("Please give us a favorable review in the App Store");
                case STRING_RATEYES:        return ccs("Yes");
                case STRING_RATENO:         return ccs("No");
                    
                case STRING_RED_WON:        return ccs("Red won");
                case STRING_GREEN_WON:      return ccs("Green won");
                case STRING_WHITE_WON:      return ccs("White won");
                case STRING_BLACK_WON:      return ccs("Black won");
                case STRING_BLUE_WON:       return ccs("Blue won");
                
                case STRING_UNDO_BTN:       return ccs("UNDO");
                case STRING_NEW_BTN:        return ccs("NEW");
                case STRING_MENU_BTN:       return ccs("MENU");
                    
                case STRING_QUESTION:       return ccs("Are you sure?");
                case STRING_ATTENTION:      return ccs("Attention");
                
                case STRING_PLAY:           return ccs("PLAY");
                case STRING_OPTIONS:        return ccs("OPTIONS");
                case STRING_RULES:          return ccs("RULES");
                case STRING_STATS:          return ccs("STATS");
                case STRING_MOREGAMES:      return ccs("MORE GAMES");
                    
                case STRING_MODES:          return ccs("GAME MODE");
                case STRING_DIFFICULTY:     return ccs("DIFFICULTY");
                case STRING_START_FORM:     return ccs("STARTING FORMATION");
                case STRING_COLORS:         return ccs("STONE SET");
                case STRING_BOARD:          return ccs("BOARD");
                case STRING_SHOW_MOVES:     return ccs("SHOW POSSIBLE MOVES");
                case STRING_LIVE_SCORE:     return ccs("LIVE SCORES");
                    
                case STRING_PVP:            return ccs("Player vs Player");
                case STRING_PVC:            return ccs("Player vs Computer");
                case STRING_EASY:           return ccs("EASY");
                case STRING_MEDIUM:         return ccs("MEDIUM");
                case STRING_HARD:           return ccs("HARD");
                case STRING_VERY_HARD:      return ccs("VERY HARD");
                case STRING_THE_HARDEST:    return ccs("THE HARDEST");
                case STRING_CROSS:          return ccs("CROSS");
                case STRING_STRAIGHT:       return ccs("STRAIGHT");
                case STRING_BLACK_WHITE:    return ccs("BLACK/WHITE");
                case STRING_RED_BLUE:       return ccs("RED/BLUE");
                case STRING_WOOD:           return ccs("WOOD");
                case STRING_OTHELLO:        return ccs("OTHELLO");
                case STRING_ON:             return ccs("ON");
                case STRING_OFF:            return ccs("OFF");
                    
                case STRING_STATS_GAMES:    return ccs("Total Games Played:");
                case STRING_STATS_WON:      return ccs("Games Won:");
                case STRING_STATS_LOST:     return ccs("Games Lost:");
                case STRING_STATS_TIED:     return ccs("Games Tied:");
                case STRING_STATS_RESET:    return ccs("RESET");
                case STRING_STATS_DETAILS:  return ccs("Details");
                
                    
			}
			return ccs("UNTRANSLATEDenGB!");
		case deDE:
			switch (stringID) {
				case STRING_LANG:			return ccs("deDE");
				case STRING_NOTICE:			return ccs("Hinweis");
				case STRING_OK:				return ccs("OK");
				case STRING_ILLEGAL:		return ccs("Illegaler Zug!");
				case STRING_MUSTPASS:		return ccs("Du musst passen.");
                case STRING_AI_MUSTPASS:	return ccs("Computer muss passen.");
				case STRING_END:			return ccs("Spielende");
				case STRING_WON:			return ccs("Du hast gewonnen");
				case STRING_LOST:			return ccs("Du hast verloren");
				case STRING_DRAW:			return ccs("Unentschieden.");
				case STRING_BACK:			return ccs("Zurück");
				case STRING_NEW:			return ccs("Neues Spiel");
                    
                case STRING_RATETITLE:      return ccs("Bewerte das Spiel!");
                case STRING_RATETHIS:       return ccs("Gib uns bitte eine gute Bewertung im App Store");
                case STRING_RATEYES:        return ccs("Ja");
                case STRING_RATENO:         return ccs("Nein");
                    
                case STRING_RED_WON:        return ccs("Rot hat gewonnen");
                case STRING_GREEN_WON:      return ccs("Grün hat gewonnen");
                case STRING_WHITE_WON:      return ccs("Weiß hat gewonnen");
                case STRING_BLACK_WON:      return ccs("Schwarz hat gewonnen");
                case STRING_BLUE_WON:       return ccs("Blau hat gewonnen");
                    
                case STRING_UNDO_BTN:       return ccs("UNDO");
                case STRING_NEW_BTN:        return ccs("NEU");
                case STRING_MENU_BTN:       return ccs("MENU");
                    
                case STRING_QUESTION:       return ccs("Bist du sicher?");
                case STRING_ATTENTION:      return ccs("Achtung");
                    
                case STRING_PLAY:           return ccs("SPIELEN");
                case STRING_OPTIONS:        return ccs("OPTIONEN");
                case STRING_RULES:          return ccs("REGELN");
                case STRING_STATS:          return ccs("STATISTIK");
                case STRING_MOREGAMES:      return ccs("MORE GAMES");
                    
                case STRING_MODES:          return ccs("Game Mode:");
                case STRING_DIFFICULTY:     return ccs("Spielstärke:");
                case STRING_START_FORM:     return ccs("Startaufstellung:");
                case STRING_COLORS:         return ccs("Farben:");
                case STRING_BOARD:          return ccs("BOARD");
                case STRING_SHOW_MOVES:     return ccs("Zeigen mögliche Schritten:");
                case STRING_LIVE_SCORE:     return ccs("Live scores:");
                    
                case STRING_PVP:            return ccs("Player vs Player");
                case STRING_PVC:            return ccs("Player vs Computer");
                case STRING_EASY:           return ccs("LEICHT");
                case STRING_MEDIUM:         return ccs("MITTEL");
                case STRING_HARD:           return ccs("SCHWER");
                case STRING_VERY_HARD:      return ccs("SEHR SCHWER");
                case STRING_THE_HARDEST:    return ccs("SCHWIERIGSTE");
                case STRING_CROSS:          return ccs("DIAGONAL");
                case STRING_STRAIGHT:       return ccs("WAAGERECHT");
                case STRING_BLACK_WHITE:    return ccs("SCHWARZ/WEISS");
                case STRING_RED_BLUE:       return ccs("ROT/BLAU");
                case STRING_WOOD:           return ccs("HOLZ");
                case STRING_OTHELLO:        return ccs("OTHELLO");
                case STRING_ON:             return ccs("ON");
                case STRING_OFF:            return ccs("OFF");
                    
                case STRING_STATS_GAMES:    return ccs("Spiele gesamt:");
                case STRING_STATS_WON:      return ccs("Gewonnen:");
                case STRING_STATS_LOST:     return ccs("Verloren:");
                case STRING_STATS_TIED:     return ccs("Unentschieden:");
                case STRING_STATS_RESET:    return ccs("LÖSCHEN");
                case STRING_STATS_DETAILS:  return ccs("Details");

                    
			}
			return ccs("UNTRANSLATEDdeDE!");
		case esES:
			switch(stringID) {
				case STRING_LANG:			return ccs("esES");
				case STRING_NOTICE:			return ccs("Aviso");
				case STRING_OK:				return ccs("OK");
				case STRING_ILLEGAL:		return ccs("Jugada no permitida!");
				case STRING_MUSTPASS:		return ccs("Tienes que pasar!");
                case STRING_AI_MUSTPASS:	return ccs("La computadora no puede moverse.");
				case STRING_END:			return ccs("Resultado");
				case STRING_WON:			return ccs("Ganado");
				case STRING_LOST:			return ccs("Perdido");
				case STRING_DRAW:			return ccs("Empate.");
				case STRING_BACK:			return ccs("Atrás");
				case STRING_NEW:			return ccs("Nuevo partido");
                    
                case STRING_RATETITLE:      return ccs("Califica este juego!");
                case STRING_RATETHIS:       return ccs("Por favor, danos una opinión favorable en la App Store");
                case STRING_RATEYES:        return ccs("Sí");
                case STRING_RATENO:         return ccs("No");
                    
                case STRING_RED_WON:        return ccs("El rojo ha ganado");
                case STRING_GREEN_WON:      return ccs("El verde ha ganado");
                case STRING_WHITE_WON:      return ccs("El blanco ha ganado");
                case STRING_BLACK_WON:      return ccs("El negro ha ganado");
                case STRING_BLUE_WON:       return ccs("El azul ha ganado");
                    
                case STRING_UNDO_BTN:       return ccs("ANULA");
                case STRING_NEW_BTN:        return ccs("NUEVO");
                case STRING_MENU_BTN:       return ccs("MENU");
                    
                case STRING_QUESTION:       return ccs("¿Está seguro?");
                case STRING_ATTENTION:      return ccs("¡Atención");
                    
                case STRING_PLAY:           return ccs("JUGAR");
                case STRING_OPTIONS:        return ccs("OPCIONES");
                case STRING_RULES:          return ccs("REGLAS");
                case STRING_STATS:          return ccs("ESTADISTICAS");
                case STRING_MOREGAMES:      return ccs("OTROS JUEGOS");
                    
                case STRING_MODES:          return ccs("Game Mode:");
                case STRING_DIFFICULTY:     return ccs("Dificultad:");
                case STRING_START_FORM:     return ccs("Formación de apertura:");
                case STRING_COLORS:         return ccs("Colores:");
                case STRING_BOARD:          return ccs("TABLERO");
                case STRING_SHOW_MOVES:     return ccs("Mostrar movimientos posibles:");
                case STRING_LIVE_SCORE:     return ccs("Live scores:");
                    
                case STRING_PVP:            return ccs("Player vs Player");
                case STRING_PVC:            return ccs("Player vs Computer");
                case STRING_EASY:           return ccs("FACIL");
                case STRING_MEDIUM:         return ccs("MEDIO");
                case STRING_HARD:           return ccs("DIFICIL");
                case STRING_VERY_HARD:      return ccs("MUY DIFICIL");
                case STRING_THE_HARDEST:    return ccs("LO MÁS DIFICIL");
                case STRING_CROSS:          return ccs("DIAGONAL");
                case STRING_STRAIGHT:       return ccs("RECTO");
                case STRING_BLACK_WHITE:    return ccs("NEGRO/BLANCO");
                case STRING_RED_BLUE:       return ccs("ROJO/AZUL");
                case STRING_WOOD:           return ccs("MADERA");
                case STRING_OTHELLO:        return ccs("OTHELLO");
                case STRING_ON:             return ccs("ON");
                case STRING_OFF:            return ccs("OFF");
                    
                case STRING_STATS_GAMES:    return ccs("Total de partidos:");
                case STRING_STATS_WON:      return ccs("Ganados:");
                case STRING_STATS_LOST:     return ccs("Perdidos:");
                case STRING_STATS_TIED:     return ccs("Empate:");
                case STRING_STATS_RESET:    return ccs("BORAR");
                case STRING_STATS_DETAILS:  return ccs("Detalles");

                    
			}
			return ccs("UNTRANSLATEDesES!");
		case frFR:
			switch(stringID) {
				case STRING_LANG:			return ccs("frFR");
				case STRING_NOTICE:			return ccs("Avertissement");
				case STRING_OK:				return ccs("OK");
				case STRING_ILLEGAL:		return ccs("Tour pas autorisé!");
				case STRING_MUSTPASS:		return ccs("Passez, s'il vous plaît!");
                case STRING_AI_MUSTPASS:	return ccs("Ordinateur ne peut pas se déplacer.");
				case STRING_END:			return ccs("Résultat");
				case STRING_WON:			return ccs("Vous avez gagné");
				case STRING_LOST:			return ccs("Vous avez perdu");
				case STRING_DRAW:			return ccs("Nul.");
				case STRING_BACK:			return ccs("Retour");
				case STRING_NEW:			return ccs("Nouveau jeu");
                    
                case STRING_RATETITLE:      return ccs("Noter ce jeu!");
                case STRING_RATETHIS:       return ccs("S'il vous plaît, donnez votre avis dans l' App Store");
                case STRING_RATEYES:        return ccs("Oui");
                case STRING_RATENO:         return ccs("Non");
                    
                case STRING_RED_WON:        return ccs("Le rouge a gagné");
                case STRING_GREEN_WON:      return ccs("Le vert a gagné");
                case STRING_WHITE_WON:      return ccs("Le blanc a gagné");
                case STRING_BLACK_WON:      return ccs("Le noir a gagné");
                case STRING_BLUE_WON:       return ccs("Le bleu a gagné");
                    
                case STRING_UNDO_BTN:       return ccs("ANNU.");
                case STRING_NEW_BTN:        return ccs("NOUV.");
                case STRING_MENU_BTN:       return ccs("MENU");
                    
                case STRING_QUESTION:       return ccs("Etes-vous sûr?");
                case STRING_ATTENTION:      return ccs("Attention");
                    
                case STRING_PLAY:           return ccs("JOUER");
                case STRING_OPTIONS:        return ccs("REGLAGES");
                case STRING_RULES:          return ccs("REGLES");
                case STRING_STATS:          return ccs("STATISTIQUE");
                case STRING_MOREGAMES:      return ccs("D'AUTRES JEUX");
                
                case STRING_MODES:          return ccs("Game Mode:");
                case STRING_DIFFICULTY:     return ccs("Difficulté:");
                case STRING_START_FORM:     return ccs("Position de départ:");
                case STRING_COLORS:         return ccs("Couleurs:");
                case STRING_BOARD:          return ccs("TABLEAU");
                case STRING_SHOW_MOVES:     return ccs("Afficher Coups Possibles");
                case STRING_LIVE_SCORE:     return ccs("Live scores:");
                    
                case STRING_PVP:            return ccs("Player vs Player");
                case STRING_PVC:            return ccs("Player vs Computer");
                case STRING_EASY:           return ccs("FACILE");
                case STRING_MEDIUM:         return ccs("MOYENNE");
                case STRING_HARD:           return ccs("DIFFICILE");
                case STRING_VERY_HARD:      return ccs("TRÈS DIFFICILE");
                case STRING_THE_HARDEST:    return ccs("LE PLUS DIFFICILE");
                case STRING_CROSS:          return ccs("DIAGONALE");
                case STRING_STRAIGHT:       return ccs("PARALLELES");
                case STRING_BLACK_WHITE:    return ccs("NOIR/BLANC");
                case STRING_RED_BLUE:       return ccs("ROUGE/BLEU");
                case STRING_WOOD:           return ccs("BOIS");
                case STRING_OTHELLO:        return ccs("OTHELLO");
                case STRING_ON:             return ccs("ON");
                case STRING_OFF:            return ccs("OFF");
                    
                case STRING_STATS_GAMES:    return ccs("Nombre de jeux:");
                case STRING_STATS_WON:      return ccs("Gagnés:");
                case STRING_STATS_LOST:     return ccs("Perdus:");
                case STRING_STATS_TIED:     return ccs("Nul:");
                case STRING_STATS_RESET:    return ccs("EFFACER");
                case STRING_STATS_DETAILS:  return ccs("Détails");

                    
			}
			return ccs("UNTRANSLATEDfrFR!");
		case itIT:
			switch(stringID) {
				case STRING_LANG:			return ccs("itIT");
				case STRING_NOTICE:			return ccs("Avviso");
				case STRING_OK:				return ccs("OK");
				case STRING_ILLEGAL:		return ccs("Turno non consentito!");
				case STRING_MUSTPASS:		return ccs("Salta, per favore!");
                case STRING_AI_MUSTPASS:	return ccs("Il computer non può muoversi.");
				case STRING_END:			return ccs("Risultato");
				case STRING_WON:			return ccs("Hai vinto");
				case STRING_LOST:			return ccs("Hai perso");
				case STRING_DRAW:			return ccs("artito legato.");
				case STRING_BACK:			return ccs("Indietro");
				case STRING_NEW:			return ccs("Nuovo partito");
                    
                case STRING_RATETITLE:      return ccs("Vota questo gioco!");
                case STRING_RATETHIS:       return ccs("Vi preghiamo di darci una buona recensione in App Store");
                case STRING_RATEYES:        return ccs("Si");
                case STRING_RATENO:         return ccs("No");
                    
                case STRING_RED_WON:        return ccs("Ha vinto il rosso");
                case STRING_GREEN_WON:      return ccs("Ha vinto il verde");
                case STRING_WHITE_WON:      return ccs("Ha vinto il bianco");
                case STRING_BLACK_WON:      return ccs("Ha vinto il nero");
                case STRING_BLUE_WON:       return ccs("Ha vinto il blu");
                
                case STRING_UNDO_BTN:       return ccs("DIS.");
                case STRING_NEW_BTN:        return ccs("NEW");
                case STRING_MENU_BTN:       return ccs("MENU");
                    
                case STRING_QUESTION:       return ccs("Sei sicuro?");
                case STRING_ATTENTION:      return ccs("Attenzione");
                    
                case STRING_PLAY:           return ccs("GIOCARE");
                case STRING_OPTIONS:        return ccs("OPZIONI");
                case STRING_RULES:          return ccs("REGOLE");
                case STRING_STATS:          return ccs("STATISTICHE");
                case STRING_MOREGAMES:      return ccs("ALTRI GIOCHI");
                    
                case STRING_MODES:          return ccs("Game Mode:");
                case STRING_DIFFICULTY:     return ccs("Difficoltà:");
                case STRING_START_FORM:     return ccs("Configurazione iniziale:");
                case STRING_COLORS:         return ccs("Colori:");
                case STRING_BOARD:          return ccs("PENSIONE");
                case STRING_SHOW_MOVES:     return ccs("Mostra possibili mosse:");
                case STRING_LIVE_SCORE:     return ccs("Live scores:");
                    
                case STRING_PVP:            return ccs("Player vs Player");
                case STRING_PVC:            return ccs("Player vs Computer");
                case STRING_EASY:           return ccs("FACILE");
                case STRING_MEDIUM:         return ccs("MEDIO");
                case STRING_HARD:           return ccs("DIFFICILE");
                case STRING_VERY_HARD:      return ccs("MOLTO DIFFICILE");
                case STRING_THE_HARDEST:    return ccs("LA COSA PIÙ DIFFICILE");
                case STRING_CROSS:          return ccs("DIAGONALE");
                case STRING_STRAIGHT:       return ccs("PARALLELA");
                case STRING_BLACK_WHITE:    return ccs("NERO/BIANCO");
                case STRING_RED_BLUE:       return ccs("ROSSO/BLU");
                case STRING_WOOD:           return ccs("LEGNO");
                case STRING_OTHELLO:        return ccs("OTHELLO");
                case STRING_ON:             return ccs("ON");
                case STRING_OFF:            return ccs("OFF");
                    
                case STRING_STATS_GAMES:    return ccs("Partite in totale:");
                case STRING_STATS_WON:      return ccs("Vinte:");
                case STRING_STATS_LOST:     return ccs("Perse:");
                case STRING_STATS_TIED:     return ccs("Legate:");
                case STRING_STATS_RESET:    return ccs("CANCELLARE");
                case STRING_STATS_DETAILS:  return ccs("Dettagli");

                    
			}
			return ccs("UNTRANSLATEDitIT!");
        case jaJP:
			switch(stringID) {
				case STRING_LANG:			return ccs("jaJP");
				case STRING_NOTICE:			return ccs("警告");
				case STRING_OK:				return ccs("OK");
				case STRING_ILLEGAL:		return ccs("その移動は無効です！");
				case STRING_MUSTPASS:		return ccs("パスしなければなりません。");
                case STRING_AI_MUSTPASS:	return ccs("コンピュータが移動することはできません");
				case STRING_END:			return ccs("結果");
				case STRING_WON:			return ccs("あなたが勝ちました");
				case STRING_LOST:			return ccs("あなたが負けました");
				case STRING_DRAW:			return ccs("ゲームは引き分けです");
				case STRING_BACK:			return ccs("戻る");
				case STRING_NEW:			return ccs("新しいゲーム");
                    
                case STRING_RATETITLE:      return ccs("このゲームを評価してください");
                case STRING_RATETHIS:       return ccs("AppStoreの上でこのゲームを評価してください");
                case STRING_RATEYES:        return ccs("はい");
                case STRING_RATENO:         return ccs("いいえ");
                    
                case STRING_RED_WON:        return ccs("赤の勝ち");
                case STRING_GREEN_WON:      return ccs("緑の勝ち");
                case STRING_WHITE_WON:      return ccs("白の勝ち");
                case STRING_BLACK_WON:      return ccs("黒の勝ち");
                case STRING_BLUE_WON:       return ccs("青の勝ち");
                    
                case STRING_UNDO_BTN:       return ccs("取り消し");
                case STRING_NEW_BTN:        return ccs("新");
                case STRING_MENU_BTN:       return ccs("メニュー");
                
                case STRING_QUESTION:       return ccs("本当に？");
                case STRING_ATTENTION:      return ccs("注目");
                    
                case STRING_PLAY:           return ccs("ゲーム開始<");
                case STRING_OPTIONS:        return ccs("オプション<");
                case STRING_RULES:          return ccs("ルール");
                case STRING_STATS:          return ccs("スタッツ");
                case STRING_MOREGAMES:      return ccs("もっとゲームをする");
                
                case STRING_MODES:          return ccs("Game Mode:");
                case STRING_DIFFICULTY:     return ccs("難易度:");
                case STRING_START_FORM:     return ccs("開始時の位置:");
                case STRING_COLORS:         return ccs("カラー:");
                case STRING_BOARD:          return ccs("ボード");
                case STRING_SHOW_MOVES:     return ccs("可能な動きを見せる");
                case STRING_LIVE_SCORE:     return ccs("Live scores:");
                    
                case STRING_PVP:            return ccs("Player vs Player");
                case STRING_PVC:            return ccs("Player vs Computer");
                case STRING_EASY:           return ccs("初級");
                case STRING_MEDIUM:         return ccs("中級");
                case STRING_HARD:           return ccs("上級");
                case STRING_VERY_HARD:      return ccs("一生懸命");
                case STRING_THE_HARDEST:    return ccs("一番難しい");
                case STRING_CROSS:          return ccs("クロス");
                case STRING_STRAIGHT:       return ccs("ストレート");
                case STRING_BLACK_WHITE:    return ccs("黒／白");
                case STRING_RED_BLUE:       return ccs("赤/青");
                case STRING_WOOD:           return ccs("ウッド");
                case STRING_OTHELLO:        return ccs("Othello");
                case STRING_ON:             return ccs("ON");
                case STRING_OFF:            return ccs("OFF");
                    
                case STRING_STATS_GAMES:    return ccs("総ゲーム数:");
                case STRING_STATS_WON:      return ccs("勝ち:");
                case STRING_STATS_LOST:     return ccs("負け:");
                case STRING_STATS_TIED:     return ccs("同点:");
                case STRING_STATS_RESET:    return ccs("リセット");
                case STRING_STATS_DETAILS:  return ccs("細部");

                    
			}
			return ccs("UNTRANSLATEDjaJP!");
	}

}