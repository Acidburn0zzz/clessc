#include "LessStylesheet.h"
#include "LessMediaQuery.h"

#include <config.h>

#ifdef WITH_LIBGLOG
#include <glog/logging.h>
#endif

LessStylesheet::LessStylesheet() {
}

LessStylesheet::~LessStylesheet() {
}

LessRuleset* LessStylesheet::createLessRuleset() {
  LessRuleset* r = new LessRuleset();
  
#ifdef WITH_LIBGLOG
  VLOG(3) << "Creating LessRuleset";
#endif
  
  addRuleset(*r);
  lessrulesets.push_back(r);
  r->setLessStylesheet(*this);
  return r;
}

Mixin* LessStylesheet::createMixin() {
  Mixin* m = new Mixin();
  
#ifdef WITH_LIBGLOG
  VLOG(3) << "Creating mixin";
#endif
  
  addStatement(*m);
  m->setLessStylesheet(*this);
  return m;
}

LessMediaQuery* LessStylesheet::createLessMediaQuery() {
  LessMediaQuery* q = new LessMediaQuery();
  
#ifdef WITH_LIBGLOG
  VLOG(3) << "Adding Media Query";
#endif
  
  addStatement(*q);
  q->setLessStylesheet(*this);
  return q;
}

void LessStylesheet::deleteLessRuleset(LessRuleset &ruleset) {
  lessrulesets.remove(&ruleset);
  deleteStatement(ruleset);
}

void LessStylesheet::deleteMixin(Mixin &mixin) {
  deleteStatement(mixin);
}
  
void LessStylesheet::getLessRulesets(list<LessRuleset*> &rulesetList,
                                     const Mixin &mixin) {
  list<LessRuleset*>::iterator i;
  
  for (i = lessrulesets.begin(); i != lessrulesets.end();
       i++) {

    (*i)->getLessRulesets(rulesetList, mixin, mixin.name.begin());
  }
}

void LessStylesheet::getExtensions(std::list<Extension> &extensions) {
  std::list<LessRuleset*>::iterator i;
  
  for (i = lessrulesets.begin(); i != lessrulesets.end();
       i++) {

    (*i)->getExtensions(extensions, NULL);
  }
}

void LessStylesheet::setContext(ProcessingContext* context) {
  this->context = context;
}
ProcessingContext* LessStylesheet::getContext() {
  return context;
}

void LessStylesheet::putVariable(const std::string &key, const TokenList &value) {
  map<std::string, TokenList>::iterator mit;
  
  // check if variable is alread declared
  mit = variables.find(key);
  
  if (mit != variables.end()) {
    LOG(WARNING) << "Variable " << key << " defined twice in same stylesheet.";
  }
  
  variables.insert(std::pair<std::string, TokenList>(key, value));  
}


void LessStylesheet::process(Stylesheet &s) {
  map<string,TokenList> extensions;
  list<Ruleset>::iterator r_it;
  
  getContext()->pushScope(variables);
  Stylesheet::process(s);
  getContext()->popScope();
  
  /*extensions = getExtensions(&extensions);

  for (r_it = s->getRulesets()->begin();
       r_it != s->getRulesets()->end();
       r_it++) {
    // (*r_it)->getSelector()
  }
  */
}
