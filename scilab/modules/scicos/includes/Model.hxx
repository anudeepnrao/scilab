/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2014-2014 - Scilab Enterprises - Clement DAVID
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

#ifndef MODEL_HXX_
#define MODEL_HXX_

#include <vector>
#include <unordered_map>
#include <string>

#include "utilities.hxx"
#include "model/BaseObject.hxx"

#include "dynlib_scicos.h"

namespace org_scilab_modules_scicos
{

class SCICOS_IMPEXP Model
{
public:
    Model();
    ~Model();

    /*
     * Controller wrapped methods
     */

    ScicosID createObject(kind_t k);
    unsigned referenceObject(const ScicosID uid);
    unsigned& referenceCount(ScicosID uid);
    void deleteObject(ScicosID uid);

    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, double& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, int& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, bool& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, std::string& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, ScicosID& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, std::vector<double>& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, std::vector<int>& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, std::vector< std::string >& v) const;
    bool getObjectProperty(ScicosID uid, kind_t k, object_properties_t p, std::vector<ScicosID>& v) const;

    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, double v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, int v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, bool v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, ScicosID v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, std::string v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, const std::vector<double>& v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, const std::vector<int>& v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, const std::vector< std::string >& v);
    update_status_t setObjectProperty(ScicosID uid, kind_t k, object_properties_t p, const std::vector<ScicosID>& v);

    /*
     * Model custom methods
     */

    model::BaseObject* getObject(ScicosID uid) const;
    template<typename T>
    T* getObject(ScicosID uid) const
    {
        return static_cast<T*>(getObject(uid));
    };

    model::Datatype* flyweight(const model::Datatype& d);
    void erase(model::Datatype* d);

private:
    ScicosID lastId;
    bool has_looped;

    struct ModelObject
    {
        ModelObject(model::BaseObject* o) : m_o(o), m_refCounter(0) {}

        model::BaseObject* m_o;
        unsigned m_refCounter;
    };

    typedef std::unordered_map<ScicosID, ModelObject > objects_map_t;
    objects_map_t allObjects;

    typedef std::vector<model::Datatype*> datatypes_set_t;
    datatypes_set_t datatypes;
};

} /* namespace org_scilab_modules_scicos */

#endif /* MODEL_HXX_ */