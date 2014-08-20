/**************************************************************************
**
** Copyright (c) 2014 Carel Combrink
**
** This file is part of the SpellChecker Plugin, a Qt Creator plugin.
**
** The SpellChecker Plugin is free software: you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public License as
** published by the Free Software Foundation, either version 3 of the
** License, or (at your option) any later version.
**
** The SpellChecker Plugin is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with the SpellChecker Plugin.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "ISpellChecker.h"
#include "Word.h"

using namespace SpellChecker;

void ISpellChecker::spellcheckWords(const QString &fileName, const WordList &words)
{
    Word misspelledWord;
    WordList misspelledWords;
    WordList::ConstIterator iter = words.constBegin();
    while(iter != words.end()) {
        bool spellingMistake = isSpellingMistake((*iter).text);
        /* Check to see if the char after the word is a period. If it is,
         * add the period to the word an see if it passes the checker. */
        if((spellingMistake == true)
                && ((*iter).charAfter == QLatin1Char('.'))) {
            /* Recheck the word with the period added */
            spellingMistake = isSpellingMistake((*iter).text + QLatin1Char('.'));
        }

        if(spellingMistake == true) {
            misspelledWord = (*iter);
            getSuggestionsForWord(misspelledWord.text, misspelledWord.suggestions);
            /* Add the word to the local list of misspelled words. */
            misspelledWords.append(misspelledWord);
        }
        ++iter;
    }
    emit misspelledWordsForFile(fileName, misspelledWords);
}
//--------------------------------------------------
